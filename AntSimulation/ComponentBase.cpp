module component;

import gameObject;

ComponentBase::ComponentBase(GameObject& _owner)
{
	owner = &_owner;
}