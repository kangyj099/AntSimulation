export module utils;

import <algorithm>;
import <random>;

import common;

export namespace Utils
{
	bool IsSameSign(short _a, short _b);
	bool IsSameSign(int _a, int _b);
	bool IsSameSign(float _a, float _b);
	bool IsSameSign(double _a, double _b);

	/// <summary>
	/// 유효한 방향값인지 확인
	/// </summary>
	/// <param name="_dir">검증 필요한 방향</param>
	/// <returns></returns>
	bool IsValidDirection(Direction8 _dir);
	ConsolePos FieldPositionToConsolePos(FieldPos _position);

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

	int GetRandomInt(int _min, int _max);
	float GetRandomFloat(float _min, float _max);
}
