module gameObject;

import ant;
import antHome;
import food;

/// <summary>
/// 타입에 맞는 게임 오브젝트를 생성하여 유니크포인트를 반환
/// </summary>
/// <param name="_objType">생성할 오브젝트 타입</param>
/// <param name="_field">오브젝트가 위치한 필드</param>
/// <returns>생성한 오브젝트 유니크포인터</returns>
std::unique_ptr<GameObject> CreateGameObject(ObjectType _objType, Field& _field)
{
	switch (_objType)
	{
	case ObjectType::Ant: return std::make_unique<Ant>(_field);  break;
	case ObjectType::AntHome:  return std::make_unique<AntHome>(_field); break;

	default: return nullptr;
	}
}
