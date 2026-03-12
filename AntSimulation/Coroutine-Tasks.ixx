export module Coroutine:Tasks;

import <coroutine>;
import <chrono>;

import :Scheduler;

export struct BasicTask {
	struct promise_type {
		BasicTask get_return_object() { return BasicTask{ std::coroutine_handle<promise_type>::from_promise(*this) }; }	// 핸들 return
		std::suspend_never initial_suspend() { return {}; }	// 바로 시작
		std::suspend_never final_suspend() noexcept { return {}; }	// Task 바로 정리
		void return_void() {}
		void unhandled_exception() { __debugbreak(); }
	};

	// 코루틴 핸들
	std::coroutine_handle<promise_type> handle;

	// 생성/소멸자
	BasicTask(std::coroutine_handle<promise_type> _h) : handle(_h) {}
	~BasicTask()
	{
		if (handle)
		{
			handle.destroy();
		}
	}

	/// <summary>
	/// 코루틴 재개
	/// </summary>
	void resume() {
		// 재개
		if (false == handle.done())	// .done() == true : 과거완료, 했었던 것... : 지금 끝난 상태
		{
			handle.resume();
		}
	}
};

// 코루틴 co_await 대기시간 조건 정의
export struct SleepAwaiter {
	std::chrono::steady_clock::time_point end;	// 대기 종료 시간

	// 생성자, 종료시간 필수세팅
	SleepAwaiter(std::chrono::milliseconds _awaitDuration) : end(std::chrono::steady_clock::now() + _awaitDuration)
	{
	}

	// time_poit now가 end 시점을 지났으면 true, suspend 하지 않음
	bool await_ready() const { return std::chrono::steady_clock::now() >= end; }
	// suspend될 때 호출, 스케줄러에 등록
	void await_suspend(std::coroutine_handle<> handle) {
		Scheduler::GetInstance().AddScheduleTask(handle, [](auto end = this->end) {return std::chrono::steady_clock::now() >= end; });
	};
	// resume 후 반환 (void, 뭐 없음)
	auto await_resume() {};
};

