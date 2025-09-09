module gameManager;

import <iostream>;
import <chrono>;

import console;
import utils;
import gameObject;	// DELETE: 에디터 빨간줄때문에 추가
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

		auto home = std::make_unique<AntHome>(field, homePos);
		antHome = home.get();
		objects.push_back(std::move(home));
	}

	// 개미 생성
	for (int i = 0; i < Constants::c_GAME_antCount; ++i)
	{
		auto ant = std::make_unique<Ant>(field);
		std::string name = "개미" + std::to_string(ants.size());
		ant->Setting({ 0,0 }, name, 2.0f);

		auto antPtr = ant.get();
		ants.push_back(antPtr);
		antHome->EnterAnt(*antPtr);	// 개미는 집에서 시작함

		objects.push_back(std::move(ant));
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

	logManager.AddLog(LogType::None, "논로그");
	logManager.AddLog(LogType::State, "개미가 먹이를 발견했다.");
	logManager.AddLog(LogType::Action, "개미가 먹이를 주웠다.");
	logManager.AddLog(LogType::Outcome, "집에 보관한 먹이 1개");
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
};
