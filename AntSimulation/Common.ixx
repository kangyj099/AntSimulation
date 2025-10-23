export module common;

/// <summary>
/// 필드에서의 위치
/// </summary>
export struct FieldPos {
	short x;
	short y;

	FieldPos() : x(0), y(0) {}
	FieldPos(short _x, short _y) : x(_x), y(_y) {}

	FieldPos operator +(const FieldPos& other) const
	{
		return FieldPos(x + other.x, y + other.y);
	}
	FieldPos& operator +=(const FieldPos& other)
	{
		x += other.x;	y += other.y;
		return *this;
	}
	FieldPos operator -(const FieldPos& other) const
	{
		return FieldPos(x - other.x, y - other.y);
	}
	FieldPos& operator -=(const FieldPos& other)
	{
		x -= other.x;	y -= other.y;
		return *this;
	}
	FieldPos operator *(float multiFactor) const
	{
		return FieldPos(static_cast<short>(x * multiFactor), static_cast<short>(y * multiFactor));
	}
	FieldPos& operator *=(float multiFactor)
	{
		x = static_cast<short>(x * multiFactor);	y = static_cast<short>(y * multiFactor);
		return *this;
	}
	FieldPos operator /(float divFactor) const
	{
		return FieldPos(static_cast<short>(x / divFactor), static_cast<short>(y / divFactor));
	}
	FieldPos& operator /=(float divFactor)
	{
		x = static_cast<short>(x / divFactor);	y = static_cast<short>(y / divFactor);
		return *this;
	}
	bool operator ==(const FieldPos& other) const
	{
		return (x == other.x) && (y == other.y);
	}
};

/// <summary>
/// 콘솔 화면에서의 위치
/// </summary>
export struct ConsolePos {
	short x;
	short y;

	ConsolePos() : x(0), y(0) {}
	ConsolePos(short _x, short _y) : x(_x), y(_y) {}

	ConsolePos operator +(const ConsolePos& other) const
	{
		return ConsolePos(x + other.x, y + other.y);
	}
	ConsolePos& operator +=(const ConsolePos& other)
	{
		x += other.x;	y += other.y;
		return *this;
	}
	ConsolePos operator -(const ConsolePos& other) const
	{
		return ConsolePos(x - other.x, y - other.y);
	}
	ConsolePos& operator -=(const ConsolePos& other)
	{
		x -= other.x;	y -= other.y;
		return *this;
	}
	ConsolePos operator *(float multiFactor) const
	{
		return ConsolePos(static_cast<short>(x * multiFactor), static_cast<short>(y * multiFactor));
	}
	ConsolePos& operator *=(float multiFactor)
	{
		x = static_cast<short>(x * multiFactor);	y = static_cast<short>(y * multiFactor);
		return *this;
	}
	ConsolePos operator /(float divFactor) const
	{
		return ConsolePos(static_cast<short>(x / divFactor), static_cast<short>(y / divFactor));
	}
	ConsolePos& operator /=(float divFactor)
	{
		x = static_cast<short>(x / divFactor);	y = static_cast<short>(y / divFactor);
		return *this;
	}
	bool operator ==(const ConsolePos& other) const
	{
		return (x == other.x) && (y == other.y);
	}
};

// 8방향
export enum class Direction8
{
	None = -1,

	Up = 0,    // ↑
	UpRight,   // ↗
	Right,     // →
	DownRight, // ↘
	Down,      // ↓
	DownLeft,  // ↙
	Left,      // ←
	UpLeft,    // ↖

	Count
};

// 이동 결과
export enum class MoveResult
{
	None = -1,		// 이동 시도 안함
	Success = 0,	// 이동 성공
	BlockWall,		// 이동 실패(범위 벗어남)
	BlockObstacle,	// 이동 실패(막힘)
	NotValidPos,	// 출발지나 목적지가 유효한 값이 아님
	TileObjectProblom,
};

// 색상 정의
export enum class Color : unsigned short
{
	Black = 0,
	DarkBlue = 1,
	DarkGreen = 2,
	DarkCyan = 3,
	DarkRed = 4,
	DarkMagenta = 5,
	DarkYellow = 6,
	Gray = 7,
	DarkGray = 8,
	Blue = 9,
	Green = 10,
	Cyan = 11,
	Red = 12,
	Magenta = 13,
	Yellow = 14,
	White = 15,
};

// 오브젝트
export enum class ObjectType
{
	None = -1,

	Ant = 0,
	AntHome,
	Food,

	Count
};

export enum class CollisionType
{
	None = -1,

	Overlap = 0,
	Block,

	Count
};

export class GameObject;
export struct CollisionInfo {
	CollisionType type;
	GameObject* occupantObject;	// 박힌 돌
	GameObject* visitorObject;	// 들어온 돌

	CollisionInfo() {
		type = CollisionType::None;
		occupantObject = nullptr;
		visitorObject = nullptr;
	}

	bool Set(CollisionType _type, GameObject* _occupantObj, GameObject* _visitorObj)
	{
		if (CollisionType::None >= _type || CollisionType::Count <= _type
			|| nullptr == _occupantObj || nullptr == _visitorObj)
		{
			return false;
		}

		type = _type;
		occupantObject = _occupantObj;
		visitorObject = _visitorObj;

		return true;
	}

	bool IsValidInfo()
	{
		if (CollisionType::None >= type || CollisionType::Count <= type
			|| nullptr == occupantObject || nullptr == visitorObject)
		{
			return false;
		}

		return true;
	}
};

/////////////////////////////////
// 상수
export namespace Constants
{
	/////////////////////////////////
	// 인게임 정보
	const short c_GAME_antCount = 10;	// 개미 수
	const short c_GAME_foodCount = 20;	// 먹이 수
	const short c_GAME_homeCount = 1;	// 집 수
	const short c_GAME_obstacleCount = 30;	// 장애물 수

	const float c_GAME_antSpeedMin = 1.0f;	// 개미 속도 최소(칸/초)
	const float c_GAME_antSpeedMax = 3.0f;	// 개미 속도 최대(칸/초)
	const float c_GAME_antWeightMin = 2.0f;	// 개미 무게 최소
	const float c_GAME_antWeightMax = 7.0f;	// 개미 무게 최대
	
	const float c_GAME_foodWeightMin = 5.0f;	// 먹이 무게 최소
	const float c_GAME_foodWeightMax = 20.0f;	// 먹이 무게 최대

	const float c_GAME_defaultWeightMG = 2.0f;	// 기본 무게 밀리그람

	const float c_GAME_antCarryFoodWeightRatio = 4.0f; // 개미가 본인 무게당 들 수 있는 먹이 무게 비율

	const short c_GAME_homeExitAntDurationMs = 2400;	// 집에서 개미 방출하는 주기 밀리세컨드


	/////////////////////////////////
	// 로그
	const short c_LOG_printLine = 5;	// 로그 출력 줄 수

	/////////////////////////////////
	// 필드
	const short c_FIELD_width = 40;
	const short c_FIELD_height = 20;
	const short c_FIELD_toScreenXScale = 2;

	/////////////////////////////////
	// 화면 출력 관련
	const short c_SCREEN_width = 80;
	const short c_SCREEN_height = 26;

	const short c_SCREEN_fieldStartX = 0;
	const short c_SCREEN_fieldStartY = 0;

	const short c_SCREEN_logStartX = 0;
	const short c_SCREEN_logStartY = c_SCREEN_height - c_LOG_printLine;

	/////////////////////////////////
	// 색상
	const Color c_COLOR_defaultBG = Color::Black;
	const Color c_COLOR_defaultText = Color::White;

	/////////////////////////////////
	// 이동
	// 방향
	typedef FieldPos Direction8Pos;

	// 8방향 좌표 변화량
	const inline Direction8Pos c_FIELD_directions[8] = {
		{ 0, -1 },   // Up
		{ 1, -1 },   // UpRight
		{ 1, 0 },    // Right
		{ 1, 1 },    // DownRight
		{ 0, 1 },    // Down
		{ -1, 1 },   // DownLeft
		{ -1, 0 },   // Left
		{ -1, -1 }   // UpLeft
	};
}
