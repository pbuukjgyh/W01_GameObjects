#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

TextureComponent::TextureComponent(std::shared_ptr<dae::GameObject>& pOwner, const std::string& fileName):
	ObjectComponent(pOwner),
	m_pTexture{ dae::ResourceManager::GetInstance().LoadTexture(fileName)}
{

}

TextureComponent::TextureComponent(std::shared_ptr<dae::GameObject>& pOwner):
	ObjectComponent(pOwner)
{
}

void TextureComponent::ChangeTexture(const std::string& newFileName)
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(newFileName);
}

void TextureComponent::Update(float /*deltaTime*/)
{
	
}

void TextureComponent::Render() const
{
	BasicRender(m_pTexture.get());
}
