export module interface;

import common;

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