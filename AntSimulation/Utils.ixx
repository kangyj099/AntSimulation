export module utils;

import <algorithm>;

import common;

export namespace Utils
{
	/// <summary>
	/// 유효한 방향값인지 확인
	/// </summary>
	/// <param name="_dir">검증 필요한 방향</param>
	/// <returns></returns>
	bool IsValidDirection(Constants::Direction8 _dir);
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