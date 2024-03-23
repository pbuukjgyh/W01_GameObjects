#pragma once
#include "ObjectComponent.h"
#include "GameObject.h"

class RotatingComponent: public ObjectComponent
{
public:
	RotatingComponent(std::shared_ptr<dae::GameObject> pOwner);
	RotatingComponent(std::shared_ptr<dae::GameObject> pOwner, float radius) : RotatingComponent(pOwner){ m_radius = radius / 100; };
	RotatingComponent(std::shared_ptr<dae::GameObject> pOwner, float radius, float speed) : RotatingComponent(pOwner, radius) { m_speed = speed; };
	virtual ~RotatingComponent() = default;
	RotatingComponent(const RotatingComponent& copy) = delete;
	RotatingComponent(RotatingComponent&& move) = delete;
	RotatingComponent& operator=(const RotatingComponent& toCopy) = delete;
	RotatingComponent& operator=(RotatingComponent&& toMove) = delete;

	void Update(float deltaTime) override;

	void SetRotatingPoint(const glm::vec2 newRotatingPoint) { m_middlePosition =newRotatingPoint; }

private:
	float m_radius{25};
	float m_speed{.001f};
	float m_elapsedTime{};

	dae::GameObject* m_pOwner;
	glm::vec2 m_middlePosition;
};

