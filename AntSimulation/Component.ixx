export module component;

import common;
import interface;

export class ComponentBase : public IUpdate
{
protected:

public:
	ComponentBase() {};
	virtual ~ComponentBase() {}

	virtual void Update() override = 0;

	virtual Constants::ComponentType GetType() = 0;
};
