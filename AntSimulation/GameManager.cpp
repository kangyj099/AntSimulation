module gameManager;

import <iostream>;
import <chrono>;

import console;
import utils;
import gameObject;	// DELETE: 에디터 빨간줄때문에 추가
import antHome;
import ant;

GameManager::GameManager() : logStartPos(Constants::c_SCREEN_logStartX, Constants::c_SCREEN_logStartY), antHome(nullptr)
{
	using namespace Constants;
	objects.reserve(c_GAME_antCount + c_GAME_foodCount + c_GAME_homeCount);
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	// 게임 시작 틱
	startTime = std::chrono::steady_clock::now();

	// 게임 초기 세팅
	// 필드

	// 집 생성
	{
		FieldPos homePos(Utils::Random() % Constants::c_FIELD_width, Utils::Random() % Constants::c_FIELD_height);
		if (false == field.IsValidPos(homePos))
		{
			homePos = { 0,0 };
		}

		if (false == CreateObject(ObjectType::AntHome, homePos))
		{
			__debugbreak();
		}
	}

	// 개미 생성
	for (int i = 0; i < Constants::c_GAME_antCount; ++i)
	{
		std::string name = "개미" + std::to_string(ants.size());
		if (false == CreateObject(ObjectType::Ant, { 0,0 }, name))
		{
			continue;
		}
	}
	for (auto ant : ants)
	{
		if (nullptr == ant)
		{
			continue;
		}

		antHome->EnterAnt(*ant);	// 개미는 집에서 시작함
	}

	}

	// 로그 초기화
	logManager.Reset();

	// test
	logManager.AddLog(LogType::State, "게임 시작");
};

bool GameManager::Update()
{
	// 현재 시간
	auto now = std::chrono::steady_clock::now();

	// 경과 시간(초)
	//std::cout << "경과 시간(초): " << elapsed << std::endl;

	// 오브젝트 업데이트
	for (auto& object : objects)
	{
		if (nullptr == object)
		{
			__debugbreak();
			continue;
		}

		if (true == object->IsActive())
		{
			object->Update();
		}
	}

	// 충돌 처리
	while (0 < field.IsHaveCollisionEvent())
	{
		CollisionInfo info = field.PopCollisionInfo();

		if (false == info.IsValidInfo())
		{
			continue;
		}

		ProcessCollision(info);
	}
	

	// 로그

	return true;
};

void GameManager::Draw()
{
	// 게임 화면과 로그 경계 그리기
	GotoXY({ 0, Constants::c_SCREEN_logStartY - 1 });
	for (int i = 0; i < Constants::c_SCREEN_width; ++i)
	{
		PrintText("=");
	}

	// 게임 화면 그리기
	for (auto& object : objects)
	{
		if (nullptr == object)
		{
			__debugbreak();
		}

		if (true == object->IsActive())
		{
			object->Draw();
		}
	}

	// 로그 출력
	// 로그 갱신 있을때만
	GotoXY(logStartPos);
	logManager.PrintLog();
}

void GameManager::ProcessCollision(CollisionInfo& _colInfo)
{
	switch (_colInfo.type)
	{
	case CollisionType::Block: {
		_colInfo.occupantObject->OnBlock(_colInfo.visitorObject);
		_colInfo.visitorObject->OnBlock(_colInfo.occupantObject);
	} break;
	case CollisionType::Overlap: {
		_colInfo.occupantObject->OnOverlap(_colInfo.visitorObject);
		_colInfo.visitorObject->OnOverlap(_colInfo.occupantObject);
	} break;
	default:
		break;
	}
}

bool GameManager::CreateObject(ObjectType _objType, FieldPos _pos, std::string _name)
{
	//생성 : 오브젝트 생성 -> 충돌 판정 -> 필드에 배치 -> 판정 push
	//이동: 충돌 판정->오브젝트 기존 위치 삭제->필드에 배치->판정 push

	// 유효하지 않은 위치면 생성 ㄴㄴ
	if (false == field.IsValidPos(_pos))
	{
		return false;
	}

	auto gameObject = CreateGameObject(_objType, field);
	if (nullptr == gameObject)
	{
		return false;
	}

	// 배치하고자 하는 위치에 놓으면 Block되므로 생성 자체를 안 함
	if (CollisionType::Block == field.GetCollisionType(*gameObject, _pos))
	{
		return false;
	}

	gameObject->Setting(_pos, _name, 2.0f);
	field.AddObject(*gameObject, _pos);

	auto objectPtr = gameObject.get();
	switch (gameObject->GetObjectType())
	{
	case ObjectType::Ant: {
		ants.push_back(dynamic_cast<Ant*>(objectPtr));
	} break;
	case ObjectType::AntHome: {
		antHome = dynamic_cast<AntHome*>(objectPtr);
	} break;
	default:;
	}

	objects.push_back(std::move(gameObject));

	return true;
}
