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
	auto pParentShared = m_pParent.lock();
	if (pParent == this || pParent == pParentShared.get()) return;
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

	if (pParentShared)
	{
		for (auto it = pParentShared->m_pChildren.begin(); it != pParentShared->m_pChildren.end();++it)
		{
			pParentShared->m_pChildren.erase(it);
		}
	}
	std::shared_ptr<GameObject> pNewParentShared(pParent);
	m_pParent = pNewParentShared;
	if (pNewParentShared) pNewParentShared->AddChild(this);
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
	std::shared_ptr<GameObject> pShared(pChild);
	m_pChildren.emplace_back(pShared);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	for (const auto& obj : m_pChildren)
	{
		if (obj.get() == pChild) obj->SetParent(nullptr);
	}
}

void dae::GameObject::SetPositionDirty()
{
	m_ShouldUpdateTransform = true;
	for (auto& pChild : m_pChildren) 
	{ 
		pChild->SetPositionDirty(); 
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
		auto pParentShared = m_pParent.lock();
		if (pParentShared == nullptr)
			m_worldPosition = m_localPosition;
		else
			m_worldPosition = pParentShared->GetWorldPosition() + m_localPosition;
	}
	m_ShouldUpdateTransform = false;
}
