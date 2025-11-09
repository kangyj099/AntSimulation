export module inputManager;

import <queue>;
import <chrono>;

import singleton;
import common;

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

export class InputManager : public Singleton<InputManager>
{
private:
	std::queue<InputEvent> frontInputQueue;	// 외부에서 갖다 쓰는 버퍼
	std::queue<InputEvent> backInputQueue;	// 내부에서 이벤트 기록하는 버퍼

	// HANDLE cpp 정의
	void* inputHandlePtr = nullptr;

	std::thread inputThread;
	mutable std::mutex queueMutex;
	bool isRunning;

public:
	InputManager();
	~InputManager() override;

	void Init();
	void Release();

	void Start();
	void Stop();

	bool SwapQueues();

	std::queue<InputEvent>& GetInputEvetQueue();

private:
	void InputThreadFunc();
	void HandleMouseEvent(ConsolePos pos, unsigned long eventFlags, unsigned long btnState);
};
