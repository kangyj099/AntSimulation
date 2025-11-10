export module gameManager;

import <memory>;
import <chrono>;

import singleton;
import common;
import field;

export class GameObject;
export class AntHome;
export class Ant;
export class Food;

export class GameManager : public Singleton<GameManager>
{
private:
	// 게임 시작 시간
	std::chrono::steady_clock::time_point startTime;

	// 필드
	Field field;

	// 오브젝트들
	std::vector<std::unique_ptr<GameObject>> objects;
	// 집
	AntHome* antHome;

	// 로그
	ConsolePos logStartPos;

public:
	void Init();
	void Release();

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
	void ProcessCollision(CollisionInfo& _colInfo);
	void ProcessInputEvent();

	bool CreateObject(ObjectType _objType, FieldPos _pos, std::string _name = "", float _weight = Constants::c_GAME_defaultWeightMG);
	bool ProcessRemoveReserved();
};

