export module interfaces;

import core;

export struct IUpdate {
	virtual bool Update() = 0;
protected:
	virtual ~IUpdate() = default;
};

export struct IDraw {
	virtual void Draw() = 0;
protected:
	virtual ~IDraw() = default;
};

// 게임매니저 랩핑 인터페이스
export class IGameManager : public IUpdate, public IDraw {
public:
	static IGameManager& GetInstance();	// 게임매니저 싱글톤 인스턴스 반환

	virtual void Init() = 0;

	virtual Field& GetField() = 0;

protected:
	IGameManager() = default;
	virtual ~IGameManager() = default;
};