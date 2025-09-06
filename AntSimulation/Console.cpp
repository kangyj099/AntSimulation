module console;

#include <windows.h>

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
