module;
#include <windows.h>

module console;

import <string>;
import common;

HANDLE GameScreenBuffers[2]; int curGameBufferIndex = 0;
HANDLE& GetBackBuffer()
{
	return GameScreenBuffers[(curGameBufferIndex + 1) % 2];
}

void ConsoleSetting(int _consoleWidth, int _consoleHeight, std::string _title)
{
	char cmd[100];
	sprintf_s(cmd, "mode con cols=%d lines=%d | title %s"
		, _consoleWidth, _consoleHeight, _title.c_str());
	system(cmd);

	ScreenBufferSetting();
}

void CursorSetting(int _size, bool _isVisible)
{
	CONSOLE_CURSOR_INFO consoleCursor = {};
	consoleCursor.dwSize =
		consoleCursor.bVisible = _isVisible ? TRUE : FALSE; //커서 숨기기
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursor);
}

bool GotoXY(ConsolePos _pos)
{
	if (0 > _pos.x || Constants::c_SCREEN_width <= _pos.x
		|| 0 > _pos.y || Constants::c_SCREEN_height <= _pos.y)
	{
		// 화면 사이즈 벗어난 곳으로 커서 옮기려고 시도하면 에러
		__debugbreak();
		return false;
	}

	COORD Cur = { _pos.x, _pos.y };
	if (TRUE != SetConsoleCursorPosition(GetBackBuffer(), Cur))
	{
		return false;
	}
	return true;
}

void ScreenBufferSetting()
{
	GameScreenBuffers[0] =
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	GameScreenBuffers[1] =
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	SetConsoleActiveScreenBuffer(GameScreenBuffers[curGameBufferIndex]);
}

void SwapScreenBuffer()
{
	SetConsoleActiveScreenBuffer(GetBackBuffer());
	++curGameBufferIndex;
	if (2 <= curGameBufferIndex)
	{
		curGameBufferIndex = 0;
	}

	ClearBuffer();
}

void ClearBuffer()
{
	DWORD written = 0;
	// \x1b:이스케이프 문자, [0J:커서부터 끝까지 지우기, [1J:시작부터 커서까지 지우기, [2J:화면 전체 지우기
	PCSTR sequence = "\x1b[2J";
	WriteConsole(GetBackBuffer(), sequence, (DWORD)strlen(sequence), &written, NULL);
}

void PrintText(std::string _printText, Constants::Color _bgColor, Constants::Color _textColor)
{
	HANDLE consoleHandle = GetBackBuffer();

	// 콘솔 출력 핸들
	CONSOLE_SCREEN_BUFFER_INFO oldColors;

	// 기존 색상 기억
	GetConsoleScreenBufferInfo(consoleHandle, &oldColors);

	// 색 세팅, 텍스트 출력
	SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(_bgColor) << 4 | static_cast<WORD>(_textColor));
	DWORD writeText = 0;
	WriteConsole(GetBackBuffer(), _printText.c_str(), _printText.length(), &writeText, NULL);

	// 원래 색으로 되돌리기
	SetConsoleTextAttribute(consoleHandle, oldColors.wAttributes);
}
