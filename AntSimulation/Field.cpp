module field;

import <array>;

import gameObject;
import ant;

Field::Field() : antHome(nullptr)
{
	// 타일 초기화
	// 필드 크기만큼 크기 확보
	tiles.resize(Constants::c_FIELD_width);
	// 타일에 자기 위치 넣기
	for (int x = 0; x < Constants::c_FIELD_width; ++x)
	{
		tiles[x].reserve(Constants::c_FIELD_height);
		for (int y = 0; y < Constants::c_FIELD_height; ++y)
		{
			tiles[x].emplace_back(x, y);
		}
	}
}

Field::~Field()
{

}

bool Field::AddObject(GameObject& _object, FieldPos _tilePos)
{
	// 정상적인 필드 위치가 아니면 안됨
	Tile* tile = GetTile(_tilePos);
	if (nullptr == tile)
	{
		return false;
	}

	auto colInfos = tile->GetCollisionInfos(_object);

	// 이벤트 push
	while (false == colInfos.empty())
	{
		PushCollisionInfo(colInfos.front());
		colInfos.pop();
	}

	return tile->AddObject(_object);
}

bool Field::RemoveObject(GameObject& _object, FieldPos _tilePos)
{
	// 정상적인 필드 위치가 아니면 안됨
	Tile* tile = GetTile(_tilePos);
	if (nullptr == tile)
	{
		return false;
	}

	// Todo: 오브젝트 정보 캐싱

	// 오브젝트 셀에서 제외
	return tile->RemoveObject(_object);
}

MoveResult Field::MoveObject(GameObject& _object, FieldPos _from, FieldPos _to)
{
	if (false == IsValidPos(_from) || false == IsValidPos(_to))
	{
		return MoveResult::NotValidPos;
	}

	if (_from == _to)
	{
		return MoveResult::None;	// 이동 시도 안함
	}

	Tile* fromTile = GetTile(_from);
	Tile* toTile = GetTile(_to);

	// 정상적인 필드 위치가 아니면 안됨
	if (nullptr == fromTile || nullptr == toTile)
	{
		return MoveResult::NotValidPos;
	}

	//from에 실제로 _object가 있는지 확인
	if (false == fromTile->IsContains(_object)
		|| true == toTile->IsContains(_object))
	{
		return MoveResult::TileObjectProblom;
	}

	CollisionType colType = toTile->GetCollisionType(_object);

	// 블록됨
	if (CollisionType::Block == colType)
	{
		auto tmpColInfoQueue = toTile->GetCollisionInfos(_object);

		// 이벤트 push
		while (false == tmpColInfoQueue.empty())
		{
			PushCollisionInfo(tmpColInfoQueue.front());
			tmpColInfoQueue.pop();
		}
		return MoveResult::BlockObstacle;
	}

	// 이동 진행
	if (false == RemoveObject(_object, _from))
	{
		return MoveResult::TileObjectProblom;
	}

	if (false == AddObject(_object, _to))
	{
		// 추가 실패하면 이동 취소
		if (false == AddObject(_object, _from))
		{
			// Todo: 이동 취소 실패하면 집으로 돌려보내기
		}

		return MoveResult::TileObjectProblom;
	}

	// 이동 성공
	_object.SetPos(_to);

	return MoveResult::Success;
}

bool Field::IsValidPos(FieldPos _pos) const
{
	if (_pos.x < 0 || _pos.x >= Constants::c_FIELD_width
		|| _pos.y < 0 || _pos.y >= Constants::c_FIELD_height)
	{
		return false;
	}

	return true;
}


std::array<bool, static_cast<int>(Direction8::Count)> Field::GetDirectionAvailableArray(FieldPos _centerPos)
{
	std::array<bool, static_cast<int>(Direction8::Count)> directionAvailableArr = {};
	std::fill(directionAvailableArr.begin(), directionAvailableArr.end(), true);

	for (int i = 0; i < static_cast<int>(Direction8::Count); ++i)
	{
		auto dirPos = Constants::c_FIELD_directions[i];

		if (false == IsValidPos(_centerPos + dirPos))
		{
			directionAvailableArr[i] = false;
			continue;
		}

		// Todo: 장애물 케이스 추가
	}

	return directionAvailableArr;
}

unsigned short Field::GetTileCountUntilBlock(FieldPos _pos, Direction8 _dir)
{
	unsigned short tileCount = 0;

	if (false == Utils::IsValidDirection(_dir))
	{
		return tileCount;
	}

	Constants::Direction8Pos dirPos = Constants::c_FIELD_directions[static_cast<int>(_dir)];

	FieldPos checkPos = _pos;

	// 한번 실행할 때마다 한 칸씩 전진해보기
	do {
		checkPos += dirPos;
	} while (true == IsValidPos(checkPos) && ++tileCount);	// 조건에 맞으면 tileCount 증가

	return tileCount;
}

CollisionType Field::GetCollisionType(GameObject& _object, FieldPos _pos)
{
	if (false == IsValidPos(_pos))
	{
		return CollisionType::None;
	}

	Tile* tile = GetTile(_pos);
	if (nullptr == tile)
	{
		return CollisionType::None;
	}

	return tile->GetCollisionType(_object);
}

void Field::PushCollisionInfo(CollisionInfo _colInfo)
{
	if (false == _colInfo.IsValidInfo())
	{
		return;
	}

	collisionInfos.push(_colInfo);
}

CollisionInfo Field::PopCollisionInfo()
{
	if (true == collisionInfos.empty())
	{
		return CollisionInfo();
	}

	CollisionInfo info = collisionInfos.front();
	collisionInfos.pop();

	return info;
}

bool Field::AntPickUpObject(Ant& _ant, GameObject& _pickedObject)
{
	if (true == _ant.IsCarringObject())
	{
		return false;
	}

	// 내가 나를 들면 안됨
	if (&_ant == &_pickedObject)
	{
		return false;
	}

	// 같은 좌표에 있어야만 주울 수 있음
	FieldPos antPos = _ant.GetPos();
	if (antPos != _pickedObject.GetPos())
	{
		return false;
	}

	Tile* tile = GetTile(antPos);

	if (false == tile->IsContains(_ant) || false == tile->IsContains(_pickedObject))
	{
		return false;
	}

	bool removeResult = tile->RemoveObject(_pickedObject);

	return removeResult;
}

Tile* Field::GetTile(FieldPos _pos)
{
	Tile* tile = nullptr;
	if (false == IsValidPos(_pos))
	{
		return tile;
	}

	tile = &tiles[_pos.x][_pos.y];
	return tile;
}

CollisionType Tile::GetCollisionType(GameObject& _object) const
{
	if (true == IsBlocked())
	{
		return CollisionType::Block;
	}

	if (0 < CountObject())
	{
		if (false == _object.IsOverlappable())
		{
			return CollisionType::Block;
		}

		return CollisionType::Overlap;
	}

	return CollisionType::None;
}

std::queue<CollisionInfo> Tile::GetCollisionInfos(GameObject& _gameObject)
{
	std::queue<CollisionInfo> resultQueue;

	CollisionType type = CollisionType::Overlap;

	if (true == IsBlocked() || false == _gameObject.IsOverlappable())
	{
		type = CollisionType::Block;
	}

	for (auto object : objects)
	{
		if (IsBlocked() == object->IsOverlappable())
		{
			continue;
		}

		CollisionInfo info;
		info.Set(type, object, &_gameObject);

		resultQueue.push(info);
	}

	return resultQueue;
}

bool Tile::AddObject(GameObject& _gameObject)
{
	if (true == IsContains(_gameObject))
	{
		return false;
	}

	if (true == isBlocked)
	{
		return false;
	}

	if (0 < objects.size() && false == _gameObject.IsOverlappable())
	{
		return false;
	}

	if (false == _gameObject.IsOverlappable())
	{
		isBlocked = true;
	}

	objects.push_back(&_gameObject);
	return true;
}

bool Tile::RemoveObject(GameObject& _gameObject)
{
	auto iter = FindObjectIterator(_gameObject);
	if (iter == objects.end())
	{
		return false;
	}

	if (false == (*iter)->IsOverlappable())
	{
		isBlocked = false;
	}

	objects.erase(iter);

	// 이론상 없어야함
	for (auto object : objects)
	{
		if (false == object->IsOverlappable())
		{
			__debugbreak();
		}
	}

	return true;
}
