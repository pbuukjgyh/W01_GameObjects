#pragma once
#include "ObjectComponent.h"
#include "GameObject.h"

class Health: public ObjectComponent
{
public:
	Health(std::shared_ptr<dae::GameObject> pOwner) : ObjectComponent(pOwner) {};

private:

};

