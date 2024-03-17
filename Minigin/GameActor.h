#pragma once
#include "GameObject.h"
#include <iostream>
#include "ObjectComponent.h"


class Walk : public ObjectComponent
{
	float m_deltaTime{};

	float m_speed{ .5f };

	std::shared_ptr<dae::GameObject> m_pOwner;

public:
	Walk(std::shared_ptr<dae::GameObject> pOwner) : ObjectComponent(pOwner) { m_pOwner = pOwner; };
	Walk(std::shared_ptr<dae::GameObject> pOwner, float speed) : ObjectComponent(pOwner), m_speed{speed} { m_pOwner = pOwner; };

	virtual void Update(float deltaTime) override
	{
		m_deltaTime = deltaTime;
	}

	void StepHorizontal()
	{
		auto pos{ m_pOwner->GetWorldPosition() };
		pos.x += m_deltaTime * m_speed;
		m_pOwner->SetLocalPosition(pos);
	}
	void StepVertical()
	{
		auto pos{ m_pOwner->GetWorldPosition() };
		pos.y += m_deltaTime * m_speed;
		m_pOwner->SetLocalPosition(pos);
	}
};