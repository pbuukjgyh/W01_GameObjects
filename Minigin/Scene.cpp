#include "Scene.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include "TextComponent.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene()
{
	for (auto& object : m_objects)
	{
		//foricebly delete objects to avoid memeory leaks
		object->~GameObject();
	}
}

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
		}

		m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), [](std::shared_ptr<GameObject> obj) { return obj->IsBeingDestroyed(); }), m_objects.end());
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

