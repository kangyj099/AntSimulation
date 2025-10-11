export module ant;

import gameObject;
import movement;

export class Ant : public GameObject
{
private:
	FieldPos antHomePos;
	GameObject* carringObject;

public:
	Ant(Field& _field);
	~Ant() override;

	virtual ObjectType GetObjectType() override { return ObjectType::Ant; }

	virtual void OnUpdate() override;
	virtual void OnDraw() override;

	virtual void OnOverlap(GameObject* _other) override;

	virtual void Reset() override;

	bool SetHomePos(FieldPos _antHome);
	bool SetCarringObject(GameObject& _object);
	bool DropCarringObject();

	bool IsCarringObject();

private:
	virtual void Init() override;
};