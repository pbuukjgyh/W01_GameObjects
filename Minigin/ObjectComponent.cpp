#include "ObjectComponent.h"
#include "Renderer.h"

void ObjectComponent::Update(float /*deltaTime*/)
{
}

void ObjectComponent::Render() const
{
	
}

ObjectComponent::ObjectComponent(const std::shared_ptr<dae::GameObject>& pOwner):
	m_pOwner{pOwner}
{
}
