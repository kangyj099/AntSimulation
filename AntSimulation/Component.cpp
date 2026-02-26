module component;

import gameObject;

Component::Component(GameObject& _owner)
{
	owner = &_owner;
}