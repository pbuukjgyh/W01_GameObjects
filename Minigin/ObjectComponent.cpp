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
	m_transform.SetPosition(newPos.x, newPos.y, newPos.z);
}

void ObjectComponent::SetPosition(float x, float y, float z)
{
	SetPosition(glm::vec3(x, y, z));
}

void ObjectComponent::SetPosition(float x, float y)
{
	SetPosition(x, y, 0);
}

void ObjectComponent::BasicRender(dae::Texture2D* pTexture, const glm::vec3& pos) const
{
	if(pTexture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
	}
}
