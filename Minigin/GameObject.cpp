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
}
