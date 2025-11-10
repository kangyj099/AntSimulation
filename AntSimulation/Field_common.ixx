export module field_common;

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

/////////////////////////////////
// 이동
// 방향
export using Direction8Pos = FieldPos;

// 8방향 좌표 변화량
export inline const Direction8Pos c_FIELD_directions[8] = {
	{ 0, -1 },   // Up
	{ 1, -1 },   // UpRight
	{ 1, 0 },    // Right
	{ 1, 1 },    // DownRight
	{ 0, 1 },    // Down
	{ -1, 1 },   // DownLeft
	{ -1, 0 },   // Left
	{ -1, -1 }   // UpLeft
};
