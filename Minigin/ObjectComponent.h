#pragma once
#include <glm\vec3.hpp>
#include "Transform.h"
#include "GameObject.h"

class ObjectComponent
{
	std::shared_ptr<dae::GameObject> m_pOwner{};
public:
	ObjectComponent() = default;
	virtual ~ObjectComponent() = default;
	ObjectComponent(const ObjectComponent& copy) = delete;
	ObjectComponent(ObjectComponent&& move) = delete;
	ObjectComponent& operator=(const ObjectComponent& toCopy) = delete;
	ObjectComponent& operator=(ObjectComponent&& toMove) = delete;

	virtual void Update(float deltaTime);
	virtual void Render() const;

	void SetTransform(const dae::Transform& newTransform) { m_transform = newTransform; }

	ObjectComponent(const std::shared_ptr<dae::GameObject>& pOwner);

protected:
	//The local transform: how far away is this component from it's owner
	dae::Transform m_transform{};

	dae::GameObject* GetOwner() const { return m_pOwner.get(); }
};

