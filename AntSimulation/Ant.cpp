module ant;

import <format>;

import utils;
import console;
import logManager;

import field;
import antHome;
import food;

import movement;

Ant::Ant() : carringFoodWeight(0.0f), isRest(false)
{
	Init();
}

Ant::~Ant()
{
}

void Ant::OnOverlap(GameObject* _other)
{
	if (nullptr == _other)
	{
		return;
	}

	if (true == IsRest())
	{
		return;
	}

	switch (_other->GetObjectType())
	{
	case ObjectType::AntHome:
	{
		// 내려놓기
		if (true == IsCarringFood())
		{
			AntHome* antHome = dynamic_cast<AntHome*>(_other);
			// 보유량 차감 먼저 하고 집에 넣기
			float weight = DownFood();
			antHome->AddFood(weight);

			// 개미가 집에 들어옴
			antHome->EnterAnt(*this);

			EnterRest();
		}
	}break;
	case ObjectType::Food:
	{
		// 줍기
		if (GetMaxCarringFoodWeight() >= carringFoodWeight)
		{
			Food* food = dynamic_cast<Food*>(_other);
			// 자원 차감 먼저 하고 들기
			float pickWeight = food->PickedUp(GetMaxCarringFoodWeight() - carringFoodWeight);
			float liftWeight = LiftFood(pickWeight);

			if (pickWeight != liftWeight)
			{
				__debugbreak();
			}
		}
	}break;
	default: {}
	}
}

void Ant::Reset()
{
}

bool Ant::SetHomePos(FieldPos _antHomePos)
{
	antHomePos = _antHomePos;
	return true;
}

float Ant::LiftFood(float _foodWeight)
{
	float addWeight = _foodWeight;
	if (GetMaxCarringFoodWeight() < carringFoodWeight + addWeight)
	{
		addWeight = GetMaxCarringFoodWeight() - carringFoodWeight;
	}

	if (addWeight > _foodWeight)
	{
		__debugbreak();
		return 0.0f;
	}

	carringFoodWeight += addWeight;
	LogManager::GetInstance().AddLog(LogType::Action, std::format("{} 음식 {} 들어올림 (현재 {})", GetName(), addWeight, carringFoodWeight));

	Movement* movement = GetComponent<Movement>(ComponentType::Movement);
	if (nullptr != movement)
	{
		movement->SetDestMove(antHomePos);
	}
	else
	{
		__debugbreak();
	}

	return addWeight;
}

float Ant::DownFood()
{
	float downFoodWeight = carringFoodWeight;
	carringFoodWeight = 0;
	LogManager::GetInstance().AddLog(LogType::Action, std::format("{} 음식 {} 내려둠", GetName(), downFoodWeight));

	Movement* movement = GetComponent<Movement>(ComponentType::Movement);
	if (nullptr != movement)
	{
		movement->SetRandomMove();
	}
	else
	{
		__debugbreak();
	}

	return downFoodWeight;
}

bool Ant::IsCarringFood()
{
	if (0.0f < carringFoodWeight)
	{
		return true;
	}

	return false;
}

void Ant::Init()
{
	Movement* movement = AddComponent<Movement>(pos, Constants::c_GAME_antSpeedMax);
	if (nullptr == movement)
	{
		__debugbreak();
	}
}

void Ant::OnUpdate()
{
	if (true == IsRest())
	{
		return;
	}
}

void Ant::OnDraw()
{
	if (true == IsRest())
	{
		return;
	}

	ConsolePos consolePos = Utils::FieldPositionToConsolePos(pos);
	GotoXY(consolePos);

	Color drawtextColor = textColor;

	if (true == IsCarringFood())
	{
		drawtextColor = Color::Cyan;
	}
	PrintText("ⓐ", bgColor, drawtextColor);
}
