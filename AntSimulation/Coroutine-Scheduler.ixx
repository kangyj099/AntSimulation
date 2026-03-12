export module Coroutine:Scheduler;

import <coroutine>;
import <queue>;
import <functional>;

import singleton;

struct ScheduledTask {
	std::coroutine_handle<> handle;	// 코루틴 핸들
	std::function<bool()> checkFunc;// 재개 시간
};

class Scheduler: public Singleton<Scheduler> {
private:
	std::vector<ScheduledTask> waitingTasks;	// 코루틴 대기열
	std::queue<std::coroutine_handle<>> readyTasks;	// resume 조건 충족된 코루틴 대기열

private:
	// waitingTasks 조건 확인, readyTasks로 이동
	void ProcessWaitingTasks()
	{
		if (true == waitingTasks.empty())
		{
			return;
		}

		waitingTasks.erase(
			std::remove_if(
				waitingTasks.begin(), waitingTasks.end(),
				[&](ScheduledTask& task) {
					if (true == task.checkFunc())
					{
						readyTasks.push(task.handle);
						return true;
					}

					return false;
				}
			)
			, waitingTasks.end()
		);
	}

	// readyTasks에 있는 코루틴 resume
	void ProcessReadyTasks()
	{
		while (false == readyTasks.empty())
		{
			auto handle = readyTasks.front();
			readyTasks.pop();

			if (false == handle.done())
			{
				handle.resume();
			}

			// done 체크하고 destroy는 여기서 안 함, BasicTask 소멸자에서 자동 처리
		}
	}


public:
	// !주의! checkFunc 람다 래퍼캡쳐 지양, 값캡쳐 ㅇ (수명관리 문제)
	void AddScheduleTask(std::coroutine_handle<> handle, std::function<bool()> checkFunc = []() {return true; })
	{
		waitingTasks.push_back({ handle, checkFunc });
	}

	void Update()
	{
		ProcessWaitingTasks();
		ProcessReadyTasks();
	}
};