module;

#include <windows.h>

module inputManager;

void InputManager::Init()
{
	// 인풋 핸들 가져오기
	inputHandlePtr = static_cast<void*>(GetStdHandle(STD_INPUT_HANDLE));
	Start();
}

void InputManager::Release()
{
	Stop();
}

void InputManager::Start()
{
	if (true == isRunning)
	{
		return;
	}

	isRunning = true;
	// 스레드 할당
	inputThread = std::thread(&InputManager::InputThreadFunc, this);
}

void InputManager::Stop()
{
	if (false == isRunning)
	{
		return;
	}

	if (true == inputThread.joinable())
	{
		inputThread.join();
	}
}

bool InputManager::SwapQueues()
{
	std::lock_guard<std::mutex> lk(queueMutex);

	// 프론트 큐 다 빼서 소모했을 때 backQueue와 스왑
	// 백에 이벤트가 쌓였을 때 스왑
	if (false == frontInputQueue.empty() || true == backInputQueue.empty())
	{
		return false;
	}

	std::swap(frontInputQueue, backInputQueue);

	return true;
}

std::queue<InputEvent>& InputManager::GetInputEvetQueue()
{
	std::lock_guard<std::mutex> lk(queueMutex);
	return frontInputQueue;
}

void InputManager::InputThreadFunc()
{
	HANDLE inputHandle = static_cast<HANDLE>(inputHandlePtr);
	if (NULL == inputHandle)
	{
		return;
	}

	DWORD numRead = 0;

	while (true == isRunning)
	{
		INPUT_RECORD record;
		if (TRUE != ReadConsoleInput(inputHandle, &record, 1, &numRead))
		{
			continue;
		}

		if (MOUSE_EVENT == record.EventType)
		{
			const MOUSE_EVENT_RECORD& mouseRecord = record.Event.MouseEvent;
			ConsolePos pos = { mouseRecord.dwMousePosition.X,mouseRecord.dwMousePosition.Y };
			HandleMouseEvent(pos, mouseRecord.dwEventFlags, mouseRecord.dwButtonState);
		}
	}
}

void InputManager::HandleMouseEvent(ConsolePos pos, unsigned long eventFlags, unsigned long btnState)
{
	InputEvent input;
	input.Reset();

	InputType type = InputType::None;
	KeyCode code = KeyCode::None;
	if (0 == eventFlags)
	{
		if (btnState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			type = InputType::ButtonDown;
			code = KeyCode::MouseLeft;
		}
		// 다른 마우스 버튼 케이스 여기에 추가
	}
	// 다른 마우스 동작 여기에 추가

	input.Set(type, code, pos);
	if (false == input.IsValidEvent())
	{
		return;
	}

	// 큐 락
	{
		std::lock_guard<std::mutex> lk(queueMutex);
		backInputQueue.push(input);
	}
}
