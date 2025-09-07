module utils;

import common;

using namespace Constants;

bool Utils::IsValidDirection(Direction8 _dir)
{
	if (Direction8::None >= _dir || Direction8::Count <= _dir)
	{
		return false;
	}

	return true;
}

ConsolePos Utils::FieldPositionToConsolePos(FieldPos _position)
{
	ConsolePos consolePos(_position.x * c_FIELD_toScreenXScale + c_SCREEN_fieldStartX, _position.y + c_SCREEN_fieldStartY);
	return consolePos;
}
