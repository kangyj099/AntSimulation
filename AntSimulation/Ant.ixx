export module ant;

import gameObject;
import movement;

export class Ant : public GameObject
{
private:

public:
	Ant(Field& _field);
	~Ant() override;

	virtual ObjectType GetObjectType() override { return ObjectType::Ant; }

	virtual void OnUpdate() override;
	virtual void OnDraw() override;

	virtual void Reset() override;
	void Setting(FieldPos _pos, std::string _name, float _weight);

private:
	void Init();
};