export module food;

import common;
import gameObject;

export class Food : public GameObject
{
private:
	virtual ObjectType GetObjectType() { return ObjectType::Food; }

public:
	Food(Field& _field);

	virtual void OnUpdate() override;
	virtual void OnDraw() override;

	virtual void OnOverlap(GameObject* _other) override;
};