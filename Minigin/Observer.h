#pragma once
#include "GameObject.h"s

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	//virtual void Notify(Event event, std::unique_ptr<dae::GameObject> pActor) = 0;
};

