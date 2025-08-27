export module gameObject;

import <string>;
import <vector>;
import <unordered_map>;

import common;
import utils;
import concepts;
import interface;
import component;

export class GameObject : IUpdate, IDraw
{
protected:
	// 필드에서의 좌표
	FieldPos pos;

	// 이름
	std::string name;

	// 무게(밀리그람단위)
	float weightMG;

private:
	// 컴포넌트
	std::unordered_map<ComponentType, ComponentBase*> allComponents;
	std::vector<IUpdate*> updateComponents;
	std::vector<IDraw*> drawComponents;

protected:
	// 컴포넌트 접근
	template<ComponentDerived T>
	T* GetComponent(ComponentType type)
	{
		if (allComponents.end() == allComponents.find(type))
		{
			return nullptr;
		}
		return dynamic_cast<T*>(allComponents[type]);
	}

public:
	GameObject();
	virtual ~GameObject();

	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;

	virtual void Reset();
	void ReleaseAllComponents();

	/// <summary>
	/// 컴포넌트 추가, 구현 기능에 따라서 각 벡터에도 추가
	/// </summary>
	/// <typeparam name="T">컴포넌트 클래스</typeparam>
	/// <param name="_component"></param>
	template<ComponentDerived T>
	T* AddComponent()
	{
		// 컴포넌트 생성
		T* component = new T();
		ComponentType type = component->GetType();

		// 컴포넌트 벡터에 추가
		if (allComponents.end() != allComponents.find(type))
		{	// 왜있음??
			__debugbreak();
			return nullptr;
		}
		allComponents[type] = component;

		// 컴파일할 때 유효성 체크, dynamic_cast 대체하여 사용
		if constexpr (std::is_base_of_v<IUpdate, T>)
		{
			updateComponents.push_back(component);
		}

		if constexpr (std::is_base_of_v<IDraw, T>)
		{
			drawComponents.push_back(component);
		}

		return component;
	}
};
