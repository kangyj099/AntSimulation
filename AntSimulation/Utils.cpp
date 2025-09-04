#pragma once
#include <windows.h>

module utils;

import <iostream>;
import <span>;

import common;

using namespace Constants;

/// <summary>
/// 특정 위치로 커서 이동
/// </summary>
/// <param name="_x">가로 위치(크기비율상 1당 0.5칸)</param>
/// <param name="_y">세로 위치(크기비율상 1당 1칸)</param>
bool Utils::GotoXY(ConsolePos _pos)
{
	if (0 > _pos.x || c_SCREEN_width <= _pos.x
		|| 0 > _pos.y || c_SCREEN_height <= _pos.y)
	{
		// 화면 사이즈 벗어난 곳으로 커서 옮기려고 시도하면 에러
		__debugbreak();
		return false;
	}

	COORD Cur = { _pos.x, _pos.y };
	if (TRUE != SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur))
	{
		return false;
	}
	return true;
}

void Utils::PrintText(std::string _printText, Color _bgColor, Color _textColor)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 콘솔 출력 핸들
	CONSOLE_SCREEN_BUFFER_INFO oldColors;

	// 기존 색상 기억
	GetConsoleScreenBufferInfo(consoleHandle, &oldColors);

	// 색 세팅, 텍스트 출력
	SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(_bgColor) << 4 | static_cast<WORD>(_textColor));
	std::cout << _printText;

	// 원래 색으로 되돌리기
	SetConsoleTextAttribute(consoleHandle, oldColors.wAttributes);
}

void Utils::FillTile(ConsolePos _pos, Color _color)
{
	if (false == GotoXY(_pos))
	{
		return;
	}

	PrintText("  ", _color);
}

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

/// <summary>
/// 스크린에 있는 모든 내용 지우기
/// </summary>
void Utils::ClearScreen()
{
	system("cls");
}
