export module field;

import <vector>;

import common;
import utils;

export class GameObject;

//Todo: 오브젝트 Add, Release 실패 이유 세분화하여 enum 만들기

struct Tile
{
	FieldPos position;
	std::vector<GameObject*> objects;// ♧weck_ptr

	Tile(short _x, short _y) : position(_x, _y) {}

	bool IsContains(GameObject& _object) const
	{
		return Utils::Contains(objects, &_object);
	}

	auto FindObjectIterator(GameObject& _object)
	{
		auto iter = std::find(objects.begin(), objects.end(), &_object);
		return iter;
	}

	bool AddObject(GameObject& _gameObject)
	{
		if (true == IsContains(_gameObject))
		{
			return false;
		}

		objects.push_back(&_gameObject);
		return true;
	}

	bool ReleaseObject(GameObject& _gameObject)
	{
		auto iter = FindObjectIterator(_gameObject);
		if (iter == objects.end())
		{
			return false;
		}

		objects.erase(iter);

		return true;
	}
};

export const int c_unfindIndex = -1;

/// <summary>
/// 게임 내에 배치된 오브젝트 정보를 가진 타일 그룹
/// </summary>
export class Field
{
private:
	// width*height 타일들. 각 셀이 게임오브젝트를 가지고있음
	std::vector<std::vector<Tile>> tiles;	//[x][y]

	GameObject* antHome;	// ♧weck_ptr

public:
	Field();
	~Field();

	bool AddObject(GameObject& _object, FieldPos _tilePos);
	bool ReleaseObject(GameObject& _object, FieldPos _tilePos);
	Constants::MoveResult MoveObject(GameObject& _object, FieldPos _from, FieldPos _to);

	/// <summary>
	/// 유효한 타일 위치인지 확인
	/// </summary>
	/// <param name="_pos">검증 필요한 위치</param>
	/// <returns></returns>
	bool IsValidPos(FieldPos _pos);

	/// <summary>
	/// 인접한 8방향 대상으로 이동 가능한 방향은 true, 이동 불가능한 방향은 false를 담은 array 반환
	/// </summary>
	/// <param name="_centerPos">중심좌표</param>
	/// <returns>8칸배열, 인접한 타일중 이동 가능한 방향은 true, 이동 불가능한 방향은 false</returns>
	std::array<bool, static_cast<int>(Constants::Direction8::Count)> GetDirectionAvailableArray(FieldPos _centerPos);

	/// <summary>
	/// 무언가로 막힐 때까지 특정 방향으로 직선으로 갈 수 있는 최대 칸 수 
	/// </summary>
	/// <param name="_pos">기준칸</param>
	/// <param name="_dir">최대 이동 가능 칸 수 구하고자 하는 방향</param>
	/// <returns>_pos에서 _dir 방향으로 중간에 막히지 않고 갈 수 있는 최대 칸 수</returns>
	unsigned short GetTileCountUntilBlock(FieldPos _pos, Constants::Direction8 _dir);
private:
	Tile* GetCell(FieldPos _pos);
};
