#include <string>
#include "GameObject.h"
#include "Renderer.h"
#include "ObjectComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for(const auto& component: m_pComponents)
	{
		component->Update(deltaTime);
	}
	for (const auto& child : m_pChildren)
	{
		child->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
	for (const auto& child : m_pChildren)
	{
		child->Render();
	}
}

void dae::GameObject::SetLocalPosition(float x, float y)
{
	SetLocalPosition(glm::vec3(x, y, 0));
}

void dae::GameObject::SetParent(GameObject* pParent, bool worldPosStays)
{
	if (pParent == this || pParent == m_pParent.get()) return;
	for (const auto& obj : m_pChildren)
	{
		if (obj.get() == this) return;
	}

	if (pParent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (worldPosStays)
			SetLocalPosition(GetWorldPosition() - pParent->GetWorldPosition());
		SetPositionDirty();
	}

	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = std::shared_ptr<GameObject>(pParent);
	if (m_pParent) m_pParent->AddChild(this);
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index)
{
	if (index < m_pChildren.size())
	{
		return m_pChildren[index];
	}

	return nullptr;
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_localPosition = pos;

	for (auto& component : m_pComponents)
	{
		component->SetPosition(GetWorldPosition() + m_localPosition);
	}

	SetPositionDirty();
}


void dae::GameObject::AddChild(GameObject* pChild)
{
	pChild->SetParent(this);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	for (const auto& obj : m_pChildren)
	{
		if (obj.get() == pChild) obj->SetParent(nullptr);
	}
}

glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_ShouldUpdateTransform)
		UpdateWorldPosition();
	return m_worldPosition;
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_ShouldUpdateTransform)
	{
		if (m_pParent == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = m_pParent->GetWorldPosition() + m_localPosition;
	}
	m_ShouldUpdateTransform = false;
}
