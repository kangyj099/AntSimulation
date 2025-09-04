module gameManager;

import <iostream>;
import <chrono>;

import utils;
import gameObject;	// DELETE: 에디터 빨간줄때문에 추가
import ant;

GameManager::GameManager() : logStartPos(Constants::c_SCREEN_logStartX, Constants::c_SCREEN_logStartY)
{
	using namespace Constants;
	objects.reserve(c_GAME_antCount + c_GAME_foodCount + c_GAME_homeCount);
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	Utils::ClearScreen();

	// 게임 시작 틱
	startTime = std::chrono::steady_clock::now();

	// 게임 초기 세팅
	// 필드

	// Todo: 집 생성

	// 개미 생성
	for (int i = 0; i < Constants::c_GAME_antCount; ++i)
	{
		Ant* ant = new Ant(field);
		objects.push_back(ant);
		ants.push_back(ant);
		std::string name = "개미";
		name += '0' + i;
		ant->Setting({ 0,0 }, name, 2.0f);
	}
	// 개미 활성화 Todo: 코루틴으로 3초간격
	(*ants.begin())->SetActive(true);

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
	for (auto object : objects)
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
	// 화면 지우기
	Utils::ClearScreen();

	// 화면 그리기
	for (auto object : objects)
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
	Utils::GotoXY(logStartPos);
	logManager.PrintLog();
};
