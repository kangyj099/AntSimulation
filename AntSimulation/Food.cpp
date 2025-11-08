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
	PrintText("F ", bgColor, textColor);
}

void Food::OnOverlap(GameObject* _other)
{
}

float Food::PickedUp(float _weightMG)
{
	if (weightMG <= 0.0f)
	{
		ReserveRemove();
		return 0.0f;
	}

	float pickedWeight = _weightMG;
	if (_weightMG > weightMG)
	{
		pickedWeight = weightMG;
	}

	weightMG -= pickedWeight;

	if (0.0f >= weightMG)
	{
		ReserveRemove();
	}

	return pickedWeight;
}

void Food::Init()
{
	bgColor = Color::Yellow;
	textColor = Color::Cyan;
}
