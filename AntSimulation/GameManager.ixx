export module gameManager;

import <memory>;
import <array>;
import <chrono>;
import <coroutine>;

import common;
import field;
import logManager;

export class GameObject;
export class AntHome;
export class Ant;

export class GameManager
{
private:
	// 게임 시작 시간
	std::chrono::steady_clock::time_point startTime;

	// 필드
	Field field;

	// 오브젝트들
	std::vector<std::unique_ptr<GameObject>> objects;
	// 개미들
	std::vector<Ant*> ants;
	// 집
	AntHome* antHome;

	// 먹이

	// 로그
	LogManager logManager;
	ConsolePos logStartPos;

public:
	GameManager();
	~GameManager();

	void Init();

	/// <summary>
	/// 게임 메인 로직 업데이트
	/// </summary>
	/// <returns>true: 평시, false: 종료</returns>
	bool Update();

	/// <summary>
	/// 게임 화면 그리기
	/// </summary>
	void Draw();

private:
	// Task AntSpawn(); Todo: n초마다 한 마리씩 등장하게 코루틴 추가
};

