module ant;

import common;
import utils;

import movement;

Ant::Ant(Field& _field) : GameObject(_field)
{
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
	Utils::FillTile(consolePos, Constants::Color::Magenta);
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