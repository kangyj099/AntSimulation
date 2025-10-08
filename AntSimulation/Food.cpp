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
	PrintText("F", bgColor, textColor);
}

void Food::OnOverlap(GameObject* _other)
{
}

void Food::Init()
{
	bgColor = Color::Yellow;
	textColor = Color::Cyan;
}