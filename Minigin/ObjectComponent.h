#pragma once
#include <glm\vec3.hpp>
#include "Transform.h"
#include "Texture2D.h"

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
	virtual void Render() const;

	void SetTransform(const dae::Transform& newTransform) { m_transform = newTransform; }
	void SetPosition(const glm::vec3& newPos);
	glm::vec3 GetPosition() const { return m_transform.GetPosition(); }

protected:
	//The local transform: how far away is this component from it's owner
	dae::Transform m_localTransform{};
	dae::Transform m_transform{};

	void BasicRender(dae::Texture2D* pTexture, const glm::vec3& pos)const;
};

