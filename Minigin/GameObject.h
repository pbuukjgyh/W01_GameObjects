#pragma once
#include <memory>
#include "Transform.h"

#include <vector>
class ObjectComponent;

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void Render() const;

		void SetPosition(float x, float y);

		void AddComponent(const std::shared_ptr<ObjectComponent>& newComponent);
		//Removes all component of type
		template <typename T>
		void RemoveComponents()
		{
			m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(),
				[](const std::shared_ptr<ObjectComponent>& comp)
				{
					return dynamic_cast<T*>(comp.get()) != nullptr;
				}), m_pComponents.end());
		}

		GameObject() = default;
		GameObject(const std::vector<std::shared_ptr<ObjectComponent>>& startComponents);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};

		std::vector<std::shared_ptr<ObjectComponent>> m_pComponents{};
	};
}
