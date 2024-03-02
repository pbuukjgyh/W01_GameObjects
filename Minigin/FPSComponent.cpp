#include "FPSComponent.h"

void FPSComponent::Update(float deltaTime)
{
    m_frameCount++;

    m_elapsedTime += deltaTime;

    float second{ 1000 };
    // If a milisecond has passed we calculate FPS
    if (m_elapsedTime >= second/10) 
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
