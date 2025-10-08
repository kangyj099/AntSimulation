module food;

import utils;
import console;

Food::Food(Field& _field) : GameObject(_field)
{
	Init();
}

void Food::OnUpdate()
{
}

void Food::OnDraw()
{
	ConsolePos consolePos = Utils::FieldPositionToConsolePos(pos);
	GotoXY(consolePos);
	PrintText("F", Color::Yellow, Color::Cyan);
}

void Food::OnOverlap(GameObject* _other)
{
}

void Food::Init()
{
}