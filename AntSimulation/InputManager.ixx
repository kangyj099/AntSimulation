export module inputManager;

import <queue>;
import <chrono>;
import <thread>;
import <mutex>;

import singleton;
import input_common;

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
