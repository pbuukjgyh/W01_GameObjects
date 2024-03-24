#pragma once

#include "Event.h"
//class dae::GameObject;

namespace dae{class GameObject;}

// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
	dae::GameObject* m_pSubject;
protected:
	dae::GameObject* GetSubject() { return m_pSubject; }
public:
	Observer(dae::GameObject* pSubject) :m_pSubject{ pSubject } {};
	virtual ~Observer() = default;
	virtual void Notify(EventType event, dae::GameObject* pActor) = 0;
};

#endif