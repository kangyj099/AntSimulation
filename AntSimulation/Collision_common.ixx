export module collision_common;

import core;

export enum class CollisionType
{
	None = -1,

	Overlap = 0,
	Block,

	Count
};


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
