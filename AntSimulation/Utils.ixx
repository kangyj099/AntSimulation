export module utils;

import <string>;
import <span>;

import common;

using namespace Constants;
export namespace Utils
{
	bool GotoXY(ConsolePos _pos);
	void PrintText(std::string _printText, Color _bgColor = c_COLOR_defaultBG, Color _textColor = c_COLOR_defaultText);
	void FillTile(ConsolePos _pos, Color _color);

	ConsolePos FieldPositionToConsolePos(FieldPos _position);
	/// <summary>
	/// 막힌 방향 제외한 나머지 방향 중에서 랜덤으로 하나 선택
	/// </summary>
	/// <param name="_blockDirections">막힌 방향</param>
	/// <returns>방향 랜덤 추출 결과</returns>
	Direction8 GetRandomDirection(std::span<Direction8>& _blockDirections);

	void ClearScreen();

}