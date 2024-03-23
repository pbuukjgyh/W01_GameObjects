#pragma once

#include "Event.h"
//class dae::GameObject;

// Forward declaration of GameObject class in observer.h
class GameObject;

// Observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;
	//virtual void Notify(Event event, std::unique_ptr<dae::GameObject> pActor) = 0;
	virtual void Notify(Event event/*, dae::GameObject* pActor*/) = 0;
};

#include "GameObject.h"

class RemainingLivesDisplay : public Observer
{
public:
	void Notify(Event event/*, dae::GameObject* pActor*/)
	{
		switch (event.m_type)
		{
		case EventType::PlayerDied:
			//health updates in pActor
			//display updates for this actor
			break;
		}
	}
};

class PointsDisplay : public Observer
{
public:
	void Notify(Event event/*, dae::GameObject pActor*/)
	{
		switch (event.m_type)
		{
		case EventType::PickedUp:
			//score updates in pActor
			//display updates for this actor
			break;
		}
	}
};

#endif