export module ant;

import field_common;
import gameObject;
import movement;

export class Ant : public GameObject
{
private:
	FieldPos antHomePos;
	float carringFoodWeight;

	bool isRest;

public:
	Ant();
	~Ant() override;

	ObjectType GetObjectType() override { return ObjectType::Ant; }

	void OnOverlap(GameObject* _other) override;

	void Reset() override;

	bool SetHomePos(FieldPos _antHome);

	bool IsCarringFood();
	float GetMaxCarringFoodWeight() { return weightMG * Constants::c_GAME_antCarryFoodWeightRatio; }

	void EnterRest() { isRest = true; }
	void ExitRest() { isRest = false; }
	bool IsRest() { return isRest; }

private:
	void Init() override;
	void OnUpdate() override;
	void OnDraw() override;

	float LiftFood(float _foodWeight);
	float DownFood();
};