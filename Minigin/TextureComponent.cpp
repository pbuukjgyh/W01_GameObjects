#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

TextureComponent::TextureComponent(const std::string& fileName):
	m_pTexture{ dae::ResourceManager::GetInstance().LoadTexture(fileName)}
{
}

void TextureComponent::ChangeTexture(const std::string& newFileName)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(newFileName);
}

void TextureComponent::Update(float /*deltaTime*/)
{
	
}

void TextureComponent::Render(const glm::vec3& ownerPos) const
{
	const auto& localPos{ m_transform.GetPosition() };
	BasicRender(m_pTexture.get(), localPos + ownerPos);
}
