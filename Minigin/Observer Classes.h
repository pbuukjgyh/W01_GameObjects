#pragma once

#include "Observer.h"

//#include "ObjectComponent.h" -> in TextComponent.h
//#include "GameObject.h" -> in ObjectComponent.h

#include "Health.h"

#ifndef OBSERVER_CLASSES_H
#define OBSERVER_CLASSES_H
#include "TextComponent.h"

class RemainingLivesDisplay : public Observer
{
	dae::GameObject* m_pDisplayObj;
public:
	RemainingLivesDisplay(dae::GameObject* pDisplayObj) : m_pDisplayObj{ pDisplayObj } {};

	virtual void Notify(EventType event, dae::GameObject* pActor) override
	{
		switch (event)
		{
		case EventType::PlayerDied:

			//if (auto pText = m_pDisplayObj->GetComponent<dae::TextComponent>(); pText != nullptr)
			if (auto pText = m_pDisplayObj->GetComponent<dae::TextComponent>(); pText != nullptr)
			{
				pText->SetText("# lives: " + std::to_string(pActor->GetComponent<Health>()->GetLives()));
			}

			break;
		}
	}
};

//class PointsDisplay : public Observer
//{
//public:
//	virtual void Notify(EventType event, dae::GameObject* pActor) override
//	{
//		switch (event)
//		{
//		case EventType::PickedUp:
//			//score updates in pActor
//			//display updates for this actor
//			break;
//		}
//	}
//};

#endif