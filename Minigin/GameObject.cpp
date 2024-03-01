#include <string>
#include "GameObject.h"
#include "Renderer.h"
#include "ObjectComponent.h"

dae::GameObject::GameObject(const std::vector<std::shared_ptr<ObjectComponent>>& startComponents):
	m_pComponents{startComponents}
{

}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for(const auto& component: m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();

	for (const auto& component : m_pComponents)
	{
		component->Render(pos);
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(const std::shared_ptr<ObjectComponent>& newComponent)
{
	m_pComponents.emplace_back(newComponent);
}

void dae::GameObject::SetParent(GameObject* pParent, bool worldPosStays = true)
{
	if (pParent == this) return;
	for (const auto& obj : m_pChildren)
	{
		if (obj.get() == this) return;
	}

	//we do this first to get the parent pos before it changes
	if (worldPosStays)
	{
		glm::vec3 lastParentPos{ m_pParent->m_transform.GetPosition() };
		glm::vec3 pos{ m_transform.GetPosition() + lastParentPos };
		m_transform.SetPosition(pos.x, pos.y, pos.z);
	}

	this->SetParent(nullptr);

	m_pParent->m_pChildren.emplace_back(this);
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(int index)
{
	if (index < m_pChildren.size())
	{
		return m_pChildren[index];
	}

	return nullptr;
}


void dae::GameObject::AddChild(std::shared_ptr<GameObject>& pChild)
{
	pChild->SetParent(this);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject>& pChild)
{
	for (const auto& obj : m_pChildren)
	{
		if (obj.get() == pChild.get()) obj->SetParent(nullptr);
	}
}
