#pragma once

#include "ObjectComponent.h"
#include <string>
#include "Texture2D.h"
#include <memory>

class TextureComponent : public ObjectComponent
{
public:
	TextureComponent() = default;
	TextureComponent(const std::string& fileName);
	virtual ~TextureComponent() = default;
	TextureComponent(const TextureComponent& copy) = delete;
	TextureComponent(TextureComponent&& move) = delete;
	TextureComponent& operator=(const TextureComponent& toCopy) = delete;
	TextureComponent& operator=(TextureComponent&& toMove) = delete;

	void ChangeTexture(const std::string& newFileName);

	void Update(float deltaTime) override;
	void Render(const glm::vec3& ownerPos) const override;

public:
	std::shared_ptr<dae::Texture2D> m_pTexture{};
};

