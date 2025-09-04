module movement;

import <array>;
import <random>;

import common;
import utils;
import component;
import gameObject;
import field;

using namespace Constants;

Movement::Movement(GameObject& _owner, FieldPos& _ownerPos)
	: ComponentBase(_owner), ownerPos(_ownerPos), isMoving(false)
	, direction(Direction8::None), targetMoveTileCount(0), curMoveTileCount(0)
	, speed(c_GAME_antSpeedMax)
{
}

Movement::~Movement()
{
}

void Movement::Update()
{
	// owner 이동
	if (false == isMoving)
	{
		if (false == TrySetRandomMove())
		{
			// 이동할 곳이 없음
			return;
		}
	}

	// 이동 시간 경과 체크
	auto now = std::chrono::steady_clock::now();
	auto elapsed = now - curMoveStartTime;
	auto elapsedMiliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();

	// speed * 경과시간(현재까지 이동했어야 하는 칸 수) > 지금까지 이동 칸 수 일때 이동 시도
	MoveResult moveResult = MoveResult::None;
	if (speed * elapsedMiliSeconds > 1000 * curMoveTileCount) // 이동해야하는 거리 밀리세컨드 계산
	{
		moveResult = MoveObjecOneTile(direction);
	}

	switch (moveResult)
	{
	case MoveResult::BlockWall:
	{
		// 이동 경로 재설정 후 바로 다시 움직이기
		// 방금 막힌 방향, 유턴 방향 제외
		std::array<Direction8, 2> blockedDir = { direction, static_cast<Direction8>((static_cast<int>(direction) + static_cast<int>(Direction8::Count) / 2) % static_cast<int>(Direction8::Count)) };
		if (false == TrySetRandomMove(blockedDir))
		{
			// 이동할 곳이 없음
			ResetMoveDest();
			return;
		}

		// 바로 한 칸 움직이기
		if (MoveResult::Success == MoveObjecOneTile(direction))
		{
			++curMoveTileCount;
		}
	} break;
	case MoveResult::BlockObstacle:
	{
		// 이동 경로 재설정
		// Todo: 장애물 방향 제외
	} break;
	case MoveResult::Success:
	{
		++curMoveTileCount;
		if (curMoveTileCount >= targetMoveTileCount)
		{
			// 목표 칸수 도달, 이동경로 재설성
			// 가던 방향, 유턴 제외
			std::array<Direction8, 2> blockedDir = { direction, static_cast<Direction8>((static_cast<int>(direction) + static_cast<int>(Direction8::Count) / 2) % static_cast<int>(Direction8::Count)) };
			TrySetRandomMove(blockedDir);
		}
	}
	break;
	default: {}
	}
}

void Movement::ResetMoveDest()
{
	// Todo: 이동시작시간, 이동 방향, 이동 목표 거리 초기화. 이동 종료시, 이동세팅 실패시에 사용
	curMoveStartTime = std::chrono::steady_clock::time_point{};
	direction = Direction8::None;
	targetMoveTileCount = 0;
	curMoveTileCount = 0;
	isMoving = false;
}

bool Movement::TrySetRandomMove(std::span<Direction8> _ptrSpanCostumBlockDir)
{
	// 초기화 먼저 하기
	ResetMoveDest();

	// 1. 방향 설정하기
	std::array<bool, static_cast<int>(Direction8::Count)> directionAvailables = GetOwnerField()->GetDirectionAvailableArray(ownerPos);
	// 커스텀 블락 방향 지정
	for (auto blockDir : _ptrSpanCostumBlockDir)
	{
		directionAvailables[static_cast<int>(blockDir)] = false;
	}

	// 방향 지정
	direction = GetRandomAvailableDirection(directionAvailables);

	// 방향 지정 실패 - 초기화
	if (false == Utils::IsValidDirection(direction))
	{
		ResetMoveDest();
		return false;
	}

	// 2. 이동 칸수 설정
	unsigned short maxMoveCount = GetOwnerField()->GetTileCountUntilBlock(ownerPos, direction);
	if (0 == maxMoveCount)
	{
		return false;
	}
	targetMoveTileCount = std::random_device()() % maxMoveCount + 1;	//Todo: Random 클래스로 랩핑

	// 이동 목표 칸수 설정 실패 - 초기화
	if (0 == targetMoveTileCount)
	{
		ResetMoveDest();
		return false;
	}

	curMoveStartTime = std::chrono::steady_clock::now();
	isMoving = true;

	return true;
}

MoveResult Movement::MoveObjecOneTile(Direction8 _direction)
{// Todo: 1칸 이동을 기본으로 함
	MoveResult result = MoveResult::None;

	// 목표 좌표 계산
	FieldPos destPosition = ownerPos + c_FIELD_directions[static_cast<int>(_direction)];		// 방향을 dirPos로 변경

	// 이동 검증
	// 있는가?
	result = MoveResult::BlockWall;

	// Todo: 장애물
	// result = Movement::BlockObstacle;

	if (Field* field = GetOwnerField())
	{
		result = field->MoveObject(*owner, ownerPos, destPosition);
		if (MoveResult::Success == result)
		{
			ownerPos = destPosition;
			result = MoveResult::Success;
		}
	}
	return result;
}

Field* Movement::GetOwnerField()
{
	return owner->GetField();
}

Constants::Direction8 Movement::GetRandomAvailableDirection(std::array<bool, static_cast<int>(Constants::Direction8::Count)>& _directionAvailables)
{
	Direction8 resultDir = Direction8::None;

	int randCount = 0;
	for (auto directionAvailable : _directionAvailables)
	{
		if (true == directionAvailable)
		{
			++randCount;
		}
	}

	if (0 >= randCount)
	{
		// 갈 수 있는 방향 없음
		return resultDir;
	}

	// 유효한 방향 중에서 랜덤 인덱스번째 방향 채택
	int randIndex = rand() % randCount;

	for (int i = 0; i < _directionAvailables.size(); ++i)
	{
		if (false == _directionAvailables[i])
		{
			continue;
		}
		if (0 == randIndex)
		{
			resultDir = static_cast<Direction8>(i);
			break;
		}
		--randIndex;
	}

	return resultDir;
}
