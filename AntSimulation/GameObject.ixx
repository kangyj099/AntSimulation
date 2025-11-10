export module gameObject;

import <memory>;
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

	// 오브젝트 삭제 예약
	bool isReserveRemove;

	Color bgColor;
	Color textColor;

private:
	// 컴포넌트
	std::unordered_map<ComponentType, std::unique_ptr<ComponentBase>> allComponents;
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
		return dynamic_cast<T*>(allComponents[type].get());
	}

public:
	GameObject();
	virtual ~GameObject();

	virtual ObjectType GetObjectType() = 0;

	bool Update() override;
	void Draw() override;
	virtual void Remove();

	virtual void Setting(FieldPos _pos, std::string _name, float _weight);

	// 충돌 이벤트 발생시에 호출
	virtual bool IsOverlappable() { return true; }	// 양쪽 다 true여야 겹침, 아니면 block
	virtual void OnBlock(GameObject* _other) {}
	virtual void OnOverlap(GameObject* _other) {}

	virtual void Reset();
	void ReleaseAllComponents();

	FieldPos GetPos() { return pos; }
	FieldPos SetPos(FieldPos _pos) { pos = _pos; return pos; }
	std::string GetName() { return name; }
	float GetWeight() { return weightMG; }
	Color GetBGColor() { return bgColor; }
	Color GetTextColor() { return textColor; }
	bool IsReserveRemove() { return isReserveRemove; }
	void ReserveRemove() { isReserveRemove = true; }

private:
	virtual void Init() {}
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;
	virtual void OnRemove(){};

public:
	/// <summary>
	/// 컴포넌트 추가, 구현 기능에 따라서 각 벡터에도 추가
	/// </summary>
	/// <typeparam name="T">컴포넌트 클래스</typeparam>
	/// <param name="args"></param>
	template<ComponentDerived T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		// 컴포넌트 생성
		auto component = std::make_unique<T>(*this, std::forward<Args>(args)...);
		auto compPtr = component.get();
		ComponentType type = component->GetType();

		// 컴포넌트 벡터에 추가
		if (allComponents.end() != allComponents.find(type))
		{	// 동종의 컴포넌트가 이미 있으면 문제상황
			__debugbreak();
			return nullptr;
		}
		allComponents[type] = std::move(component);

		// 컴파일할 때 유효성 체크, dynamic_cast 대체하여 사용
		if constexpr (std::is_base_of_v<IUpdate, T>)
		{
			updateComponents.push_back(compPtr);
		}

		if constexpr (std::is_base_of_v<IDraw, T>)
		{
			drawComponents.push_back(compPtr);
		}

		return compPtr;
	}
};

export std::unique_ptr<GameObject> CreateInstanceGameObject(ObjectType _objType);