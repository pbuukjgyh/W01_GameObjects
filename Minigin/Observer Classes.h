#pragma once

#include "Observer.h"

//#include "ObjectComponent.h" -> in TextComponent.h
//#include "GameObject.h" -> in ObjectComponent.h

#include "Health and Score.h"

#ifndef OBSERVER_CLASSES_H
#define OBSERVER_CLASSES_H
#include "TextComponent.h"

class RemainingLivesDisplay : public Observer
{
public:
	RemainingLivesDisplay(dae::GameObject* pDisplayObj) : Observer(pDisplayObj){};

	virtual void Notify(EventType event, dae::GameObject* pActor) override
	{
		switch (event)
		{
		case EventType::PlayerDied:

			if (auto pText = GetSubject()->GetComponent<dae::TextComponent>(); pText != nullptr)
			{
				pText->SetText("# lives: " + std::to_string(pActor->GetComponent<Health>()->GetLives()));
			}

			break;
		}
	}
};

class PointsDisplay : public Observer
{
public:
	virtual void Notify(EventType event, dae::GameObject* pActor) override
	{
		switch (event)
		{
		case EventType::PointsAddedSmall:
			if (auto pText = GetSubject()->GetComponent<dae::TextComponent>(); pText != nullptr)
			{
				pText->SetText("Score: " + std::to_string(pActor->GetComponent<Score>()->GetScore()));
			}
			break;

		case EventType::PointsAddedBig:
			if (auto pText = GetSubject()->GetComponent<dae::TextComponent>(); pText != nullptr)
			{
				pText->SetText("Score: " + std::to_string(pActor->GetComponent<Score>()->GetScore()));
			}
			break;

		}
	}
};

#endif