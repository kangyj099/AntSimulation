export module utils;

import <string>;

import common;

using namespace Constants;
export namespace Utils
{
	bool GotoXY(ConsolePos _pos);
	void PrintText(std::string _printText, Color _bgColor = c_COLOR_defaultBG, Color _textColor = c_COLOR_defaultText);
	void FillTile(ConsolePos _pos, Color _color);

	ConsolePos FieldPositionToConsolePos(FieldPos _position);

	void ClearScreen();

}