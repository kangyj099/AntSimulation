export module ant;

import gameObject;
import movement;

export class Ant : public GameObject
{
private:
	FieldPos antHomePos;
	float carringFoodWeight;

	bool isRest;

public:
	Ant(Field& _field);
	~Ant() override;

	virtual ObjectType GetObjectType() override { return ObjectType::Ant; }

	virtual void OnOverlap(GameObject* _other) override;

	virtual void Reset() override;

	bool SetHomePos(FieldPos _antHome);

	bool IsCarringFood();
	float GetMaxCarringFoodWeight() { return weightMG * Constants::c_GAME_antCarryFoodWeightRatio; }

	void EnterRest() { isRest = true; }
	void ExitRest() { isRest = false; }
	bool IsRest() { return isRest; }

private:
	virtual void Init() override;
	virtual void OnUpdate() override;
	virtual void OnDraw() override;

	float LiftFood(float _foodWeight);
	float DownFood();
};