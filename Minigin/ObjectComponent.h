#pragma once
#include <glm\vec3.hpp>
#include "Transform.h"
#include "GameObject.h"

class ObjectComponent
{
public:
	ObjectComponent() = default;
	virtual ~ObjectComponent() = default;
	ObjectComponent(const ObjectComponent& copy) = delete;
	ObjectComponent(ObjectComponent&& move) = delete;
	ObjectComponent& operator=(const ObjectComponent& toCopy) = delete;
	ObjectComponent& operator=(ObjectComponent&& toMove) = delete;

	virtual void Update(float deltaTime);
	virtual void Render(const glm::vec3& ownerPos) const;

	void SetTransform(const dae::Transform& newTransform) { m_transform = newTransform; }

protected:
	//The local transform: how far away is this component from it's owner
	dae::Transform m_transform{};

	dae::GameObject* m_pParent{};
};

