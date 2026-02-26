export module component;

import core;
import interfaces;

/////////////////////////////////
// 컴포넌트
/// <summary>
/// 컴포넌트 타입(Component 상속 클래스의 기능 종류)
/// </summary>
export enum class ComponentType
{
	None = -1,
	Movement = 0,
};

export class Component : public IUpdate
{
protected:
	GameObject* owner;

public:
	Component(GameObject& _owner);
	virtual ~Component() {}

	virtual ComponentType GetType() = 0;
};
