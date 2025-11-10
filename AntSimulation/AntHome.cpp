module antHome;

import common;
import utils;
import console;
import logManager;
import gameManager;
import ant;

AntHome::AntHome()
{
	Init();
}

AntHome::~AntHome()
{
	std::queue<Ant*> emptyQueue;
	waitingAnts.swap(emptyQueue);
}

void AntHome::OnUpdate()
{
	ExitAntRoutine();
}

void AntHome::OnDraw()
{
	ConsolePos consolePos = Utils::FieldPositionToConsolePos(pos);
	GotoXY(consolePos);
	PrintText("H", bgColor, textColor);
}

// name, weight는 기본값만을 사용함, 인자 넣어도 사용하지 않음
void AntHome::Setting(FieldPos _pos, std::string _name, float _weight)
{
	if (false == GameManager::GetInstance().GetField().IsValidPos(_pos))
	{
		_pos = { 0,0 };
	}

	pos = _pos;
}

void AntHome::EnterAnt(Ant& ant, bool isPrintLog)
{
	// 개미 집에 들어감
	GameManager::GetInstance().GetField().MoveObject(ant, ant.GetPos(), pos);

	waitingAnts.push(&ant);

	if (true == isPrintLog)
	{
		LogManager::GetInstance().AddLog(LogType::State, std::format("{}이(가) 집에 들어감", ant.GetName()));
	}
}

void AntHome::ExitAnt(bool isPrintLog)
{
	if (true == waitingAnts.empty())
	{
		return;
	}

	Ant* ant = waitingAnts.front();
	waitingAnts.pop();

	if (ant == nullptr)
		return;

	// 집 나온 개미 집 위치에서부터 시작
	GameManager::GetInstance().GetField().MoveObject(*ant, ant->GetPos(), pos);
	ant->ExitRest();

	if (true == isPrintLog)
	{
		LogManager::GetInstance().AddLog(LogType::State, std::format("{} 집에서 나옴", ant->GetName()));
	}
}

void AntHome::ExitAntRoutine()
{
	// 개미 없으면 개미내보내기 안해도 됨
	if (true == waitingAnts.empty())
	{
		return;
	}

	if (nullptr == waitingAnts.front())
	{
		waitingAnts.pop();
	}

	if (false == antExitWaitData.isAntSet)
	{
		// 개미 내보내기 세팅 안되어있으면 세팅하기
		antExitWaitData.SetExitWaitData(waitingAnts.front(), std::chrono::milliseconds(Constants::c_GAME_homeExitAntDurationMs));
	}
	else
	{
		// 개미 내보내기 가능한지 확인
		using ExitStatus = ExitAntWaitData::ExitStatus;
		switch (antExitWaitData.IsReadyExit(waitingAnts.front()))
		{
		case ExitStatus::Ready: {
			// 내보내고 초기화
			ExitAnt();	// 실제로 내보내는 부분
			antExitWaitData.Reset();
		} break;
		case ExitStatus::InvalidAnt: {
			// 개미 달라졌으니 유효하지 않음, 초기화
			__debugbreak();
			antExitWaitData.Reset();
		} break;
		case ExitStatus::Waiting:
		default: {
			// 걍 계속 대기
		} break;
		}
	}
}

void AntHome::AddFood(float _weight)
{
	stockFoodWeight += _weight;
	LogManager::GetInstance().AddLog(LogType::Outcome, std::format("집에 먹이 {} 축적. 현재 저장량 {}", _weight, stockFoodWeight));
}

void AntHome::Init()
{
	name = "HomeSweetHome";
	weightMG = 0.0f;	// 집은 무게 없음

	bgColor = Color::DarkMagenta;
	textColor = Color::DarkYellow;
}