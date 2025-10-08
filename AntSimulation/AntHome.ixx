export module antHome;

import <chrono>;
import <queue>;

import gameObject;

export class Field;
export class Ant;

// 개미가 집에 들어갈 수 있다. (집이 개미를 보유)
// 집에 있는 개미는 n초에 한 마리씩 들어온 순서대로 밖으로 내보낸다.
// 먹이를 축적한다. (먹이카운트)
struct ExitAntWaitData {
	Ant* frontAntPtr;	// 큐 맨 앞에 있는 ant 주소
	std::chrono::steady_clock::time_point antExitTime;
	bool isAntSet;

	ExitAntWaitData() { Reset(); }

	void Reset() {
		frontAntPtr = nullptr;
		antExitTime = std::chrono::steady_clock::time_point::max();
		isAntSet = false;
	}

	bool SetExitWaitData(Ant* _frontAntPtr, std::chrono::milliseconds _waitDuration)
	{
		if (nullptr == _frontAntPtr)
		{
			return false;
		}

		frontAntPtr = _frontAntPtr;
		antExitTime = std::chrono::steady_clock::now() + _waitDuration;
		isAntSet = true;
	}

	enum class ExitStatus {
		Ready, Waiting, InvalidAnt,
	};
	ExitStatus IsReadyExit(Ant* _frontAntPtr) const
	{
		if (nullptr == _frontAntPtr || _frontAntPtr != frontAntPtr)
		{
			return ExitStatus::InvalidAnt;
		}

		if (std::chrono::steady_clock::now() < antExitTime)
		{
			return ExitStatus::Waiting;
		}

		return ExitStatus::Ready;
	}
};

export class AntHome : public GameObject
{
private:
	// 개미
	std::queue<Ant*> waitingAnts;
	ExitAntWaitData antExitWaitData;

	// 먹이
	int foodCount; // 집에 축적된 먹이 개수

public:
	AntHome(Field& _field);
	~AntHome();

	virtual ObjectType GetObjectType() override { return ObjectType::AntHome; }

	virtual void OnUpdate() override;
	virtual void OnDraw() override;

	// name, weight는 기본값만을 사용함, 인자 넣어도 사용하지 않음
	virtual void Setting(FieldPos _pos, std::string _name = "HomeSweetHome", float _weight = 0.0f) override;

	// 개미
	void EnterAnt(Ant& ant); // 개미가 집에 들어감
	void ExitAnt(); // 개미가 집에서 나감
	void ExitAntRoutine();	// 집에 있는 개미 내보낼지 말지 확인

	// 먹이
	int GetFoodCount() const { return foodCount; }
	void AddFood(int count) { foodCount += count; } // 먹이 추가

private:
	virtual void Init() override;
};
