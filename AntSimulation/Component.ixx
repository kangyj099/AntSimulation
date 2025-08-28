export module component;

import common;
import interface;

export class GameObject;

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

public:
	ComponentBase() {};
	virtual ~ComponentBase() {}

	virtual void Update() override = 0;

	virtual ComponentType GetType() = 0;
};
