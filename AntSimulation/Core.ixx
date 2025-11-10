export module core;

// 자주 쓰이는 class 전방선언
export class Field;
export class GameObject;
export class Ant;
export class AntHome;

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

	const float c_GAME_antSpeedMin = 0.5f;	// 개미 속도 최소(칸/초)
	const float c_GAME_antSpeedMax = 5.0f;	// 개미 속도 최대(칸/초)
	const float c_GAME_antWeightMin = 2.0f;	// 개미 무게 최소
	const float c_GAME_antWeightMax = 7.0f;	// 개미 무게 최대

	const float c_GAME_foodWeightMin = 5.0f;	// 먹이 무게 최소
	const float c_GAME_foodWeightMax = 100.0f;	// 먹이 무게 최대

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
};
