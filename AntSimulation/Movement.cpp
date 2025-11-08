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
	: ComponentBase(_owner), ownerPos(_ownerPos), destPos({ -1,-1 }), isMoving(false), isDestMove(false)
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
		SetDirAndTileCount(SetReason::MoveStart);

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
		SetDirAndTileCount(SetReason::Blocked);
		break;
	case MoveResult::BlockObstacle:
		SetDirAndTileCount(SetReason::Obstacle);
		break;
	case MoveResult::Success:
		++curMoveTileCount;
		if (curMoveTileCount >= targetTileCount)
		{
			SetDirAndTileCount(SetReason::ReachedTarget);
		}
		break;
	default:
		break;
	}
}

bool Movement::SetDestMove(FieldPos _destPos)
{
	if (false == GetOwnerField().IsValidPos(_destPos))
	{
		// 유효하지 않은 위치
		isDestMove = false;
		return false;
	}

	ResetMove();

	// 목적지 이동 모드로 설정
	destPos = _destPos;
	isDestMove = true;
	return true;
}

bool Movement::SetRandomMove()
{
	// 유효하지 않은 위치
	destPos = { -1,-1 };
	isDestMove = false;
	return true;
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

bool Movement::SetDirAndTileCount(SetReason reason)
{
	if (true == isDestMove)
	{
		return SetDirAndTileCountToDest();
	}

	std::array<Direction8, 2> blockedDir = {};
	if (reason == SetReason::Blocked || reason == SetReason::ReachedTarget)
	{
		// 현재 방향과 유턴 방향을 제외
		blockedDir = { direction, static_cast<Direction8>((static_cast<int>(direction) + static_cast<int>(Direction8::Count) / 2) % static_cast<int>(Direction8::Count)) };
	}

	return SetDirAndTileCountRandom(blockedDir);
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
	targetTileCount = Utils::GetRandomInt(1, maxMoveCount);

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

bool Movement::SetDirAndTileCountToDest()
{
	// 목적지 이동이 아니거나, 이미 도착한 경우
	if (false == isDestMove || false == GetOwnerField().IsValidPos(destPos)
		|| ownerPos == destPos)
	{
		return false;
	}

	// 초기화 먼저 하기
	ResetMove();

	// 목적지까지 도달하기 위한 총 필요 방향과 거리
	FieldPos toDest = destPos - ownerPos;

	// 방향 설정하기 ({0,0}인 경우는 도착한 경우로 위에서 제외함)
	// 직선
	if (toDest.x == 0 || toDest.y == 0)
	{
		if (toDest.x == 0) // 수직
		{
			if (toDest.y > 0)
			{
				direction = Direction8::Down;
				targetTileCount = toDest.y;
			}
			else
			{
				direction = Direction8::Up;
				targetTileCount = -toDest.y;
			}
		}
		else // 수평
		{
			if (toDest.x > 0)
			{
				direction = Direction8::Right;
				targetTileCount = toDest.x;
			}
			else
			{
				direction = Direction8::Left;
				targetTileCount = -toDest.x;
			}
		}
	}//END 직선
	else if (abs(toDest.x) == abs(toDest.y)) // 대각선
	{
		if (toDest.x > 0) // 우측
		{
			if (toDest.y > 0)
			{
				direction = Direction8::DownRight;
			}
			else
			{
				direction = Direction8::UpRight;
			}
			targetTileCount = toDest.x;
		}
		else // 좌측
		{
			if (toDest.y > 0)
			{
				direction = Direction8::DownLeft;
			}
			else
			{
				direction = Direction8::UpLeft;
			}
			targetTileCount = -toDest.x;
		}
	}//END 대각선
	else // 대각선 직선 혼합, 랜덤 채택
	{
		// 0:대각선, 1:직선
		if (0 == Utils::GetRandomInt(0, 1))	// 대각선 우선
		{
			if (toDest.x > 0) // 우측
			{
				direction = (toDest.y > 0) ? Direction8::DownRight : Direction8::UpRight;
				targetTileCount = toDest.x;
			}
			else // 좌측
			{
				direction = (toDest.y > 0) ? Direction8::DownLeft : Direction8::UpLeft;
				targetTileCount = -toDest.x;
			}
		}
		else // 직선 우선
		{
			if (true == Utils::IsSameSign(toDest.x, toDest.y)) // 부호가 같음
			{
				if (0 < toDest.x)
				{
					if (0 < toDest.x - toDest.y) // x 방향으로 더 멀리
					{
						direction = (toDest.x > 0) ? Direction8::Right : Direction8::Left;
						targetTileCount = toDest.x - toDest.y;
					}
					else // y 방향으로 더 멀리
					{
						direction = (toDest.y > 0) ? Direction8::Down : Direction8::Up;
						targetTileCount = toDest.y - toDest.x;
					}
				}
				else // 음수
				{
					if (0 < -toDest.x + toDest.y) // x 방향으로 더 멀리
					{
						direction = (toDest.x > 0) ? Direction8::Right : Direction8::Left;
						targetTileCount = -toDest.x + toDest.y;
					}
					else // y 방향으로 더 멀리
					{
						direction = (toDest.y > 0) ? Direction8::Down : Direction8::Up;
						targetTileCount = -toDest.y + toDest.x;
					}
				}
			}
			else if (0 < toDest.x) // 부호가 다름, x가 양수
			{
				if (0 < toDest.x + toDest.y) // y가 -이지만 절대값이 더 작음, x 방향으로 더 멀리
				{
					direction = (toDest.x > 0) ? Direction8::Right : Direction8::Left;
					targetTileCount = toDest.x + toDest.y;
				}
				else // y 방향으로 더 멀리
				{
					direction = (toDest.y > 0) ? Direction8::Down : Direction8::Up;
					targetTileCount = -toDest.x - toDest.y;
				}
			}
			else // 부호가 다름, x가 음수
			{
				if (0 < -toDest.x - toDest.y) // y가 +이지만 절대값이 더 작음, x 방향으로 더 멀리
				{
					direction = (toDest.x > 0) ? Direction8::Right : Direction8::Left;
					targetTileCount = -toDest.x - toDest.y;
				}
				else // y 방향으로 더 멀리
				{
					direction = (toDest.y > 0) ? Direction8::Down : Direction8::Up;
					targetTileCount = toDest.x + toDest.y;
				}
			}
		}//END 직선우선이동
	}//END 목적지 대각선직선혼합이동

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
