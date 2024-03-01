#pragma once
#include "ObjectComponent.h"
#include <chrono>

class FPSComponent: public ObjectComponent
{
public:
	FPSComponent(std::shared_ptr<dae::GameObject>& pOwner);
	virtual ~FPSComponent() = default;
	FPSComponent(const FPSComponent& copy) = delete;
	FPSComponent(FPSComponent&& move) = delete;
	FPSComponent& operator=(const FPSComponent& toCopy) = delete;
	FPSComponent& operator=(FPSComponent&& toMove) = delete;

	virtual void Update(float deltaTime) override;
	virtual void Render() const override;

	float GetFPS() { return m_FPS; }
private:
	int m_frameCount{};
	float m_elapsedTime{};

	float m_FPS{};
};

