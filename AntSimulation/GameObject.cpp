module gameObject;

GameObject::GameObject()
{
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

void GameObject::Reset()
{
	ReleaseAllComponents();
}

void GameObject::ReleaseAllComponents()
{
	// 부착한 컴포넌트 모두 삭제
	for (auto& component : allComponents)
	{
		SafeDelete(component.second);
	}
	allComponents.clear();
	updateComponents.clear();
	drawComponents.clear();
}
