export module utils;

import contains;
import <string>;

export bool GotoXY(short _x, short _y);
export void PrintText(std::string _printText, Color _bgColor = c_COLOR_defaultBG, Color _TextColor = c_COLOR_defaultText);
export void FillTile(short _x, short _y, Color _color);

export void ClearScreen();