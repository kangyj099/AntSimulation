module field;

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
	Tile* cell = GetCell(_tilePos);
	if (nullptr == cell)
	{
		return false;
	}

	return cell->AddObject(_object);
}

bool Field::ReleaseObject(GameObject& _object, FieldPos _tilePos)
{
	// 정상적인 필드 위치가 아니면 안됨
	Tile* cell = GetCell(_tilePos);
	if (nullptr == cell)
	{
		return false;
	}

	// Todo: 오브젝트 정보 캐싱

	// 오브젝트 셀에서 제외
	return cell->ReleaseObject(_object);
}

bool Field::MoveObject(GameObject& _object, FieldPos _from, FieldPos _to)
{
	Tile* fromCell = GetCell(_from);
	Tile* toCell = GetCell(_to);

	// 정상적인 필드 위치가 아니면 안됨
	if (nullptr == fromCell || nullptr == toCell)
	{
		return false;
	}

	//from에 실제로 _object가 있는지 확인 후 from에서 to로 move
	if (false == fromCell->IsContains(_object)
		|| true == toCell->IsContains(_object))
	{
		return false;
	}

	if (false == ReleaseObject(_object, _from))
	{
		return false;
	}

	if (false == AddObject(_object, _to))
	{
		// 추가 실패하면 이동 취소
		if (false == AddObject(_object, _from))
		{
			// Todo: 이동 취소 실패하면 집으로 돌려보내기
		}

		return false;
	}

	return true;
}

bool Field::IsValidPos(FieldPos _pos)
{
	if (_pos.x < 0 || _pos.x >= Constants::c_FIELD_width
		|| _pos.y < 0 || _pos.y >= Constants::c_FIELD_height)
	{
		return false;
	}

	return true;
}


Tile* Field::GetCell(FieldPos _pos)
{
	Tile* cell = nullptr;
	if (false == IsValidPos(_pos))
	{
		return cell;
	}

	cell = &tiles[_pos.x][_pos.y];
	return cell;
}
