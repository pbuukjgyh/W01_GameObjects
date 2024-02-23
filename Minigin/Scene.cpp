#include "Scene.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	if(!m_objects.empty())
	{
		for (auto& object : m_objects)
		{
			object->Update(deltaTime);

			if (auto fps{ object->GetComponent<FPSComponent>() }; fps != nullptr)
			{
				if (auto text = object->GetComponent<TextObject>(); text != nullptr)
				{
					std::stringstream fpsText;
					fpsText << std::fixed << std::setprecision(1) << fps->GetFPS() << " FPS";

					text->SetText(fpsText.str());
				}
			}
		}
	}
}

void Scene::Render() const
{
	if(!m_objects.empty())
	{
		for (const auto& object : m_objects)
		{
			object->Render();
		}
	}
}

