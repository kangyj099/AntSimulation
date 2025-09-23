module ant;

import common;
import utils;
import console;

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
	GotoXY(consolePos);
	PrintText("ⓐ");
}

void Ant::Reset()
{
}

void Ant::Init()
{
	Movement* movement = AddComponent<Movement>(pos, Constants::c_GAME_antSpeedMax);
	if (nullptr == movement)
	{
		__debugbreak();
	}
}