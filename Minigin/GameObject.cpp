#include <string>
#include "GameObject.h"
#include "Renderer.h"
#include "ObjectComponent.h"

dae::GameObject::GameObject()
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
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(const std::shared_ptr<ObjectComponent>& newComponent)
{
	m_pComponents.emplace_back(newComponent);

	//if we haven't set our owner jet, we can do it now
	//m_pComponents[m_pComponents.size() - 1]->InitializeOwner(this);
}

void dae::GameObject::AddComponent(ObjectComponent* pNewComponent)
{
	std::shared_ptr<ObjectComponent> pObjectComponent(pNewComponent);
	AddComponent(pObjectComponent);
}
