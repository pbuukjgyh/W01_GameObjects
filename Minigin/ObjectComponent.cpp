#include "ObjectComponent.h"
#include "Renderer.h"

ObjectComponent::ObjectComponent(std::shared_ptr<dae::GameObject>& pOwner):
	m_pOwner{pOwner}
{
	m_pOwner->AddComponent(this);
}

void ObjectComponent::Update(float /*deltaTime*/)
{
}

void ObjectComponent::Render() const
{
	
}

void ObjectComponent::InitializeOwner(std::shared_ptr<dae::GameObject>& pOwner)
{
	//we can only set the owner if we don't have a owner
	if (m_pOwner != nullptr) return;

	m_pOwner = pOwner;

	//if owner doesn't have type yet we add it
	if (!m_pOwner->HasComponent<decltype(this)>(this))
	{
		m_pOwner->AddComponent(this);
	}
}

void ObjectComponent::BasicRender(dae::Texture2D* pTexture) const
{
	glm::vec3 localPos{ m_transform.GetPosition() };
	glm::vec3 ownerPos{ m_pOwner->GetPosition() };
	dae::Renderer::GetInstance().RenderTexture(*pTexture, ownerPos.x + localPos.x, ownerPos.y + localPos.y);
}
