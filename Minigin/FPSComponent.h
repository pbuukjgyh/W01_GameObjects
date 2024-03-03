#pragma once
#include "ObjectComponent.h"
#include <chrono>
#include "TextComponent.h"
#include "ResourceManager.h"

class FPSComponent: public dae::TextComponent
{
public:
	FPSComponent() :TextComponent(" ", dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)) {};
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& copy) = delete;
	FPSComponent(FPSComponent&& move) = delete;
	FPSComponent& operator=(const FPSComponent& toCopy) = delete;
	FPSComponent& operator=(FPSComponent&& toMove) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() const override;

private:
	int m_frameCount{};
	float m_elapsedTime{};

	float m_FPS{};
};

