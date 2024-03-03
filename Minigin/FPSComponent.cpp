#include "FPSComponent.h"

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

        std::stringstream fpsText;
        fpsText << std::fixed << std::setprecision(1) << m_FPS << " FPS";

        this->SetText(fpsText.str());
    }

    TextComponent::Update(deltaTime);
}

void FPSComponent::Render() const
{
    TextComponent::Render();
}
