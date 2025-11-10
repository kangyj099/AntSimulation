export module component;

import core;
import interfaces;

/////////////////////////////////
// 컴포넌트
/// <summary>
/// 컴포넌트 타입(ComponentBase 상속 클래스의 기능 종류)
/// </summary>
export enum class ComponentType
{
	None = -1,
	Movement = 0,
};

export class ComponentBase : public IUpdate
{
protected:
	GameObject* owner;

public:
	ComponentBase(GameObject& _owner);
	virtual ~ComponentBase() {}

	virtual ComponentType GetType() = 0;
};
