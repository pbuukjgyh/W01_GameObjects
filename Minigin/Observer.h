#pragma once

#include "Event.h"
//class dae::GameObject;

namespace dae{class GameObject;}

// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	virtual void Notify(EventType event, dae::GameObject* pActor) = 0;
};

#endif