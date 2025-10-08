module ant;

import common;
import utils;
import console;

import field;
import food;

import movement;

Ant::Ant(Field& _field) : GameObject(_field), carringObject(nullptr)
{
	Init();
}

Ant::~Ant()
{
}

void Ant::OnUpdate()
{
}

void Ant::OnDraw()
{
	ConsolePos consolePos = Utils::FieldPositionToConsolePos(pos);
	GotoXY(consolePos);
	PrintText("ⓐ");
}

void Ant::OnOverlap(GameObject* _other)
{
	if (nullptr == _other)
	{
		return;
	}

	switch (_other->GetObjectType())
	{
	case ObjectType::Food:
	{
		// 줍기
		if (nullptr == carringObject)
		{
			GetField().AntPickUpObject(*this, *_other);
			SetCarringObject(*_other);
		}
	}break;
	default:{}
	}
}

void Ant::Reset()
{
}

bool Ant::SetCarringObject(GameObject& _object)
{
	// 내가 나를 들면 안됨
	if (this == &_object)
	{
		return false;
	}

	// 손이 없음
	if (true == IsCarringObject())
	{
		return false;
	}

	carringObject = &_object;
	
	// 들고있는 동안 짐은 활성화 끈다
	if (true == _object.IsActive())
	{
		_object.SetActive(false);
	}

	return true;
}

bool Ant::DropCarringObject()
{
	return true;
}

bool Ant::IsCarringObject()
{
	if (nullptr != carringObject)
	{
		return true;
	}

	return false;
}

void Ant::Init()
{
	isActive = false;	// 생성해도 바로 배치하지 않음

	Movement* movement = AddComponent<Movement>(pos, Constants::c_GAME_antSpeedMax);
	if (nullptr == movement)
	{
		__debugbreak();
	}
}