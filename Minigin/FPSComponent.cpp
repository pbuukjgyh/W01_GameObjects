#include "FPSComponent.h"

FPSComponent::FPSComponent(std::shared_ptr<dae::GameObject>& pOwner):
    ObjectComponent(pOwner)
{
}

void FPSComponent::Update(float deltaTime)
{
    m_frameCount++;

    m_elapsedTime += deltaTime;

    float second{ 1000 };
    // If a second has passed we calculate FPS
    if (m_elapsedTime >= second) 
    {
        m_FPS = float(m_frameCount) / (m_elapsedTime / second);

        //reset counts
        m_frameCount = 0;
        m_elapsedTime = 0;
    }
}

void FPSComponent::Render() const
{
}
