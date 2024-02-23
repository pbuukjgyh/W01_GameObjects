#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

TextureComponent::TextureComponent(const std::string& fileName):
	m_pTexture{ dae::ResourceManager::GetInstance().LoadTexture(fileName)}
{
}

void TextureComponent::ChangeTexture(const std::string& newFileName)
{
	dae::ResourceManager::GetInstance().LoadTexture(newFileName);
}

void TextureComponent::Update(float /*deltaTime*/)
{
	
}

void TextureComponent::Render(glm::vec3 ownerPos) const
{
	glm::vec3 localPos{ m_transform.GetPosition() };
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture.get(), ownerPos.x + localPos.x, ownerPos.y + localPos.y);
}
