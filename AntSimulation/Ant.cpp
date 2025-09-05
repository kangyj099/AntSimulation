module ant;

import common;
import utils;

import movement;

Ant::Ant(Field& _field) : GameObject(_field)
{
	isActive = false;	// 생성해도 바로 배치하지 않음
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
	Utils::GotoXY(consolePos);
	Utils::PrintText("ⓐ");
}

void Ant::Reset()
{
}

void Ant::Setting(FieldPos _pos, std::string _name, float _weight)
{
	pos = _pos;
	name = _name;
	weightMG = _weight;
}

void Ant::Init()
{
	Movement* movement = AddComponent<Movement>(pos);
	if (nullptr == movement)
	{
		__debugbreak();
	}
}