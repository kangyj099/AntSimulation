module movement;

import <array>;

import common;
import utils;
import component;
import gameObject;
import field;

using namespace Constants;
using namespace std::chrono;

Movement::Movement(GameObject& _owner, FieldPos& _ownerPos, float _speed)
	: ComponentBase(_owner), ownerPos(_ownerPos), isMoving(false)
	, direction(Direction8::None), targetTileCount(0), curMoveTileCount(0)
	, speed(_speed)
	, durationPerTile(duration_cast<steady_clock::duration>(duration<double>(1.0 / _speed)))
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
		SetDirAndTileCountRandom();

		return;
	}

	// max가 초기값, 세팅 안된거
	if (steady_clock::time_point::max() == nextMoveTime)
	{
		return;
	}

	MoveResult moveResult = MoveResult::None;
	if (steady_clock::now() >= nextMoveTime) // 이동해야할 타이밍 도래했는지?
	{
		moveResult = MoveObjecOneTile(direction);
		nextMoveTime += durationPerTile;
	}

	switch (moveResult)
	{
	case MoveResult::BlockWall:
	{
		// 이동 경로 재설정 후 바로 다시 움직이기
		// 방금 막힌 방향, 유턴 방향 제외
		std::array<Direction8, 2> blockedDir = { direction, static_cast<Direction8>((static_cast<int>(direction) + static_cast<int>(Direction8::Count) / 2) % static_cast<int>(Direction8::Count)) };
		if (false == SetDirAndTileCountRandom(blockedDir))
		{
			// 이동할 곳이 없음
			ResetMove();
			return;
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
		if (curMoveTileCount >= targetTileCount)
		{
			// 목표 칸수 도달, 이동경로 재설성
			// 가던 방향, 유턴 제외
			std::array<Direction8, 2> blockedDir = { direction, static_cast<Direction8>((static_cast<int>(direction) + static_cast<int>(Direction8::Count) / 2) % static_cast<int>(Direction8::Count)) };
			SetDirAndTileCountRandom(blockedDir);
		}
	}
	break;
	default: {}
	}
}

Field& Movement::GetOwnerField()
{
	return owner->GetField();
}

void Movement::ResetMove()
{
	// 이동시작시간, 이동 방향, 이동 목표 거리 초기화. 이동 종료시, 이동세팅 실패시에 사용
	nextMoveTime = steady_clock::time_point::max();
	direction = Direction8::None;
	targetTileCount = 0;
	curMoveTileCount = 0;
	isMoving = false;
}

bool Movement::SetDirAndTileCountRandom(std::span<Direction8> _ptrSpanCostumBlockDir)
{
	// 초기화 먼저 하기
	ResetMove();

	// 1. 방향 설정하기
	std::array<bool, static_cast<int>(Direction8::Count)> directionAvailables = GetOwnerField().GetDirectionAvailableArray(ownerPos);
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
		ResetMove();
		return false;
	}

	// 2. 이동 칸수 설정
	unsigned short maxMoveCount = GetOwnerField().GetTileCountUntilBlock(ownerPos, direction);
	if (0 == maxMoveCount)
	{
		return false;
	}
	targetTileCount = Utils::Random() % maxMoveCount + 1;

	// 이동 목표 칸수 설정 실패 - 초기화
	if (0 == targetTileCount)
	{
		ResetMove();
		return false;
	}

	nextMoveTime = steady_clock::now() + durationPerTile;
	isMoving = true;

	return true;
}

MoveResult Movement::MoveObjecOneTile(Direction8 _direction)
{// Todo: 1칸 이동을 기본으로 함
	MoveResult result = MoveResult::None;

	// 목표 좌표 계산
	FieldPos destPosition = ownerPos + c_FIELD_directions[static_cast<int>(_direction)];		// 방향을 dirPos로 변경

	// 실제 필드에서 이동시켜보기
	Field& field = GetOwnerField();
	result = field.MoveObject(*owner, ownerPos, destPosition);

	return result;
}

Direction8 Movement::GetRandomAvailableDirection(std::array<bool, static_cast<int>(Direction8::Count)>& _directionAvailables)
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
