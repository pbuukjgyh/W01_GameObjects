#include "ObjectComponent.h"
#include "Renderer.h"

void ObjectComponent::Update(float /*deltaTime*/)
{
}

void ObjectComponent::Render() const
{
	
}

void ObjectComponent::SetPosition(const glm::vec3& newPos)
{
	auto componentPos = m_transform.GetPosition() - m_localTransform.GetPosition();

	m_localTransform.SetPosition(newPos.x, newPos.y, newPos.z);

	m_transform.SetPosition(newPos.x + componentPos.x, newPos.y + componentPos.y, newPos.z + componentPos.z);
}

void ObjectComponent::BasicRender(dae::Texture2D* pTexture, const glm::vec3& pos) const
{
	if(pTexture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
	}
}
