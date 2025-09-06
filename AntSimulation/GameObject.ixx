export module gameObject;

import <string>;
import <vector>;
import <unordered_map>;

import common;
import utils;
import concepts;
import interface;
import component;

export class Field;

export class GameObject : IUpdate, IDraw
{
protected:
	// 필드
	Field* field;	// ♧weak_ptr 서로 완전 독립적이니까

	// 필드에서의 좌표
	FieldPos pos;

	// 이름
	std::string name;

	// 무게(밀리그람단위)
	float weightMG;

	// 현재 활동중인지
	bool isActive;

private:
	// 컴포넌트
	std::unordered_map<ComponentType, ComponentBase*> allComponents;	// ♧shared_ptr
	std::vector<IUpdate*> updateComponents;	// ♧shared_ptr
	std::vector<IDraw*> drawComponents;	// ♧shared_ptr

protected:
	// 컴포넌트 접근
	template<ComponentDerived T>
	T* GetComponent(ComponentType type)	// ♧shared_ptr
	{
		if (allComponents.end() == allComponents.find(type))
		{
			return nullptr;
		}
		return dynamic_cast<T*>(allComponents[type]);
	}

public:
	GameObject(Field& _field);
	virtual ~GameObject();

	virtual void Update() override;
	virtual void Draw() override;

	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;

	virtual void Reset();
	void ReleaseAllComponents();

	void SetActive(bool _activeState);
	bool IsActive() { return isActive; };

	/// <summary>
	/// 컴포넌트 추가, 구현 기능에 따라서 각 벡터에도 추가
	/// </summary>
	/// <typeparam name="T">컴포넌트 클래스</typeparam>
	/// <param name="args"></param>
	template<ComponentDerived T, typename... Args>
	T* AddComponent(Args&&... args)	// ♧weak_ptr
	{
		// 컴포넌트 생성
		T* component = new T(*this, std::forward<Args>(args)...);
		ComponentType type = component->GetType();

		// 컴포넌트 벡터에 추가
		if (allComponents.end() != allComponents.find(type))
		{	// 동종의 컴포넌트가 이미 있으면 문제상황
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

	Field* GetField() { return field; }	// ♧weak_ptr
	FieldPos GetPos() { return pos; }
};
