#include "RotatingComponent.h"

RotatingComponent::RotatingComponent(dae::GameObject* pOwner): m_pOwner{pOwner}
{
	auto ownerPosition{pOwner->GetWorldPosition()};

	m_middlePosition = glm::vec2(ownerPosition.x, ownerPosition.y);
}

void RotatingComponent::Update(float deltaTime)
{
	m_elapsedTime += deltaTime;

	auto rotationPosition{glm::vec3(cosf(m_elapsedTime*m_speed) * m_radius, sinf(m_elapsedTime * m_speed) * m_radius, 0)};

	m_pOwner->SetLocalPosition(glm::vec3(rotationPosition.x + m_middlePosition.x, rotationPosition.y + m_middlePosition.y,0));
}