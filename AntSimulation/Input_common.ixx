export module input_common;

import <chrono>;

import core;

export enum class InputType
{
	None = -1,

	ButtonDown = 0,

	Count
};

export enum class KeyCode
{
	None = -1,

	MouseLeft,
	MouseRight,
	MouseWheel,

	Count
};

export class InputEvent
{
private:
	InputType type;
	KeyCode code;
	std::chrono::steady_clock::time_point timeStamp;

	ConsolePos pointerPos;

public:
	InputEvent()
	{
		Reset();
	}

	bool IsValidEvent()
	{
		if (InputType::None >= type || InputType::Count <= type
			|| KeyCode::None >= code || KeyCode::Count <= code
			|| std::chrono::steady_clock::time_point::max() == timeStamp)
		{
			return false;
		}

		return true;
	}

	void Set(InputType _type, KeyCode _code, ConsolePos _pos)
	{
		type = _type;
		code = _code;
		pointerPos = _pos;
		timeStamp = std::chrono::steady_clock::now();
	}

	void Reset()
	{
		type = InputType::None;
		code = KeyCode::None;
		pointerPos = { -1,-1 };
		timeStamp = std::chrono::steady_clock::time_point::max();
	}

	InputType GetType() { return type; }
	KeyCode GetCode() { return code; }
	ConsolePos GetPos() { return pointerPos; }
};
