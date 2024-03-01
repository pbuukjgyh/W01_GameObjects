#include "ObjectComponent.h"
#include "Renderer.h"

void ObjectComponent::Update(float /*deltaTime*/)
{
}

void ObjectComponent::Render(const glm::vec3& /*ownerPos*/) const
{
	
}

void ObjectComponent::BasicRender(dae::Texture2D* pTexture, const glm::vec3& pos) const
{
	if(pTexture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
	}
}
