export module movement;

import <chrono>;
import <span>;

import common;
import component;


using Constants::Direction8;

export class Field;

// Todo: 스피드 정보 생성해서 넣는 것 어디서 할지 정하기
export class Movement sealed : public ComponentBase
{
private:
	FieldPos& ownerPos;

	bool isMoving;	// 이동 중인지
	Direction8 direction;
	short targetMoveTileCount;	// 목표 이동 칸수
	short curMoveTileCount;	// 현재 이동 칸수
	float speed;	// 칸/s (거리1 = 1칸)
	std::chrono::steady_clock::duration durationPerTile;// 1칸 이동하는데 걸리는 주기(steady_clock 기반)
	std::chrono::steady_clock::time_point nextMoveTime; // 다음 칸 이동하는 타이밍

public:
	Movement(GameObject& _owner, FieldPos& _ownerPos, float _speed);
	virtual ~Movement();

	virtual void Update() override;

	virtual ComponentType GetType() override { return ComponentType::Movement; }
	bool IsMoving() const { return isMoving; }

	void ResetMoveDest();

	/// <summary>
	/// 이동 방향, 칸수 랜덤 설정
	/// </summary>
	/// <param name="_ptrSpanCostumBlockDir">방향 랜덤설정할 때 추가적으로 제외되어야 할 방향 목록(경로지정 상황에 따라 유턴방향 등을 막음)</_ptrSpanCostumBlockDir>
	/// <returns>이동 랜덤 설정 성공 여부</returns>
	bool TrySetRandomMove(std::span<Direction8> _ptrSpanCostumBlockDir = {});

	// 이동
	Constants::MoveResult MoveObjecOneTile(Direction8 _direction);

private:
	Field& GetOwnerField();

	/// <summary>
/// 막힌 방향 제외한 나머지 방향 중에서 랜덤으로 하나 선택
/// </summary>
/// <param name="_blockDirections">막힌 방향</param>
/// <returns>방향 랜덤 추출 결과</returns>
	Constants::Direction8 GetRandomAvailableDirection(std::array<bool, static_cast<int>(Constants::Direction8::Count)>& _directionAvailables);
};