#pragma once

#include <windows.h>

module utils;

import contains;
/// <summary>
/// 특정 위치로 커서 이동
/// </summary>
/// <param name="_x">가로 위치(크기비율상 1당 0.5칸)</param>
/// <param name="_y">세로 위치(크기비율상 1당 1칸)</param>
bool GotoXY(short _x, short _y)
{
	if (0 > _x || c_SCREEN_width <= _x
		|| 0 > _y || c_SCREEN_height <= _y)
	{
		// 화면 사이즈 벗어난 곳으로 커서 옮기려고 시도하면 에러
		__debugbreak();
		return false;
	}

	COORD Cur = { _x, _y };
	if (TRUE != SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur))
	{
		return false;
	}
	return true;
}

void PrintText(std::string _printText, Color _bgColor, Color _textColor)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 콘솔 출력 핸들
	CONSOLE_SCREEN_BUFFER_INFO oldColors;

	// 기존 색상 기억
	GetConsoleScreenBufferInfo(consoleHandle, &oldColors);

	// 색 세팅, 텍스트 출력
	SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(_bgColor) << 4 | static_cast<WORD>(_textColor));
	printf("%s", _printText.c_str());

	// 원래 색으로 되돌리기
	SetConsoleTextAttribute(consoleHandle, oldColors.wAttributes);
}

void FillTile(short _x, short _y, Color _color)
{
	if (false == GotoXY(_x, _y))
	{
		return;
	}

	PrintText("  ", _color);
}

/// <summary>
/// 스크린에 있는 모든 내용 지우기
/// </summary>
void ClearScreen()
{
	system("cls");
}