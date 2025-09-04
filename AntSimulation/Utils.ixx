export module utils;

import <algorithm>;
import <string>;
import <span>;

import common;

export namespace Utils
{
	bool GotoXY(ConsolePos _pos);
	void PrintText(std::string _printText, Constants::Color _bgColor = Constants::c_COLOR_defaultBG, Constants::Color _textColor = Constants::c_COLOR_defaultText);
	void FillTile(ConsolePos _pos, Constants::Color _color);

	/// <summary>
	/// 막힌 방향 제외한 나머지 방향 중에서 랜덤으로 하나 선택
	/// </summary>
	/// <param name="_blockDirections">막힌 방향</param>
	/// <returns>방향 랜덤 추출 결과</returns>
	Direction8 GetRandomDirection(std::span<Direction8>& _blockDirections);

	ConsolePos FieldPositionToConsolePos(FieldPos _position);
	void ClearScreen();

	/// <summary>
	/// range에 value가 포함되어 있는지 확인
	/// </summary>
	/// <typeparam name="T">Range 구조를 사용하는 자료</typeparam>
	/// <typeparam name="Range">어딘가에 정의되어있는 concept</typeparam>
	/// <param name="range">value가 있는지 확인할 자료</param>
	/// <param name="value">range에서 찾을 값</param>
	/// <returns>있으면 true 없으면 false</returns>
	template<std::ranges::range Range, typename T>
	bool Contains(const Range& _range, const T& _value)
	{
		if (_range.end() == std::find(_range.begin(), _range.end(), _value))
		{
			return false;
		}

		return true;
	}
}

// 많이 쓰일 예정이라 Utils 네임스페이스 밖으로 뺌
/// <summary>
/// 포인터 널체크 하고 삭제
/// </summary>
/// <param name="_ptr">삭제할 포인터</param>
/// <returns>삭제 성공 여부, 이미 nullptr이면 삭제 동작 진행 안 했으므로 false</returns>
export bool SafeDelete(void* _ptr)
{
	if (nullptr != _ptr)
	{
		delete _ptr;
		_ptr = nullptr;
		return true;
	}
	return false;
}