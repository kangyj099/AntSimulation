export module food;

import core;
import gameObject;

export class Food : public GameObject
{
private:
	ObjectType GetObjectType() override { return ObjectType::Food; }

public:
	Food();

	void OnUpdate() override;
	void OnDraw() override;

	void OnOverlap(GameObject* _other) override;

	float PickedUp(float _weightMG);

private:
	void Init() override;
};