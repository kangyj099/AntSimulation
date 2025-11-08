module gameObject;

import field;

GameObject::GameObject(Field& _field) : field(_field), isReserveRemove(false)
, bgColor(Constants::c_COLOR_defaultBG), textColor(Constants::c_COLOR_defaultText)
{
	field.AddObject(*this, pos);
}

GameObject::~GameObject()
{
	ReleaseAllComponents();
}

void GameObject::Update()
{
	OnUpdate();

	// 컴포넌트 업데이트
	for (IUpdate* component : updateComponents)
	{
		component->Update();
	}
}

void GameObject::Draw()
{
	OnDraw();

	// 컴포넌트 그리기
	for (IDraw* component : drawComponents)
	{
		component->Draw();
	}
}

void GameObject::Remove()
{
	OnRemove();

	field.RemoveObject(*this, GetPos());
}

void GameObject::Setting(FieldPos _pos, std::string _name, float _weight)
{
	pos = _pos;
	name = _name;
	weightMG = _weight;
}

void GameObject::Reset()
{
	ReleaseAllComponents();
}

void GameObject::ReleaseAllComponents()
{
	// 부착한 컴포넌트 모두 삭제
	allComponents.clear();
	updateComponents.clear();
	drawComponents.clear();
}
