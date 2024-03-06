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
		bool m_ShouldUpdateTransform;
	public:
		void Update(float deltaTime);
		void Render() const;

		void SetLocalPosition(float x, float y);

		template<typename T>
		void AddComponent(std::unique_ptr<T>& newComponent)
		{
			if(std::is_base_of<ObjectComponent, T>::value)
				m_pComponents.emplace_back(std::move(newComponent));
		}

		std::shared_ptr<GameObject>& GetParent() { auto pParentShared = m_pParent.lock(); return pParentShared; }
		void SetParent(GameObject* pParent, bool worldPosStays = true);

		int GetChildCount() { return int(m_pChildren.size()); }
		std::shared_ptr<GameObject> GetChildAt(int index);

		void SetLocalPosition(const glm::vec3& pos);

		//Removes all components of type
		template <typename T>
		void RemoveComponents()
		{
			//sets all removable components to the back and then makes erase erase all comps in the back
			m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(),
				[](const std::unique_ptr<ObjectComponent>& comp)
				{
					return dynamic_cast<T*>(comp.get()) != nullptr;
				}), m_pComponents.end());
		}
		//returns vector of all the types
		template <typename T>
		std::vector<std::unique_ptr<T>> GetComponents()
		{
			std::vector<std::unique_ptr<T>> components;
			for (const auto& pComp : m_pComponents) {
				if (std::unique_ptr<T> pDerived = std::dynamic_pointer_cast<T>(pComp))
				{
					components.push_back(pDerived);
				}
			}
			return components;
		}
		//returns the first of a type
		template <typename T>
		std::unique_ptr<T> GetComponent()
		{
			std::vector<std::unique_ptr<T>> components;
			for (const auto& pComp : m_pComponents) {
				if (std::unique_ptr<T> pDerived = std::dynamic_pointer_cast<T>(pComp))
				{
					return pDerived;
				}
			}
			return nullptr;
		}

		template <typename T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		void Destroy() { m_shouldDestroy = true; }
		bool IsBeingDestroyed() { return m_shouldDestroy; }

		void SetPositionDirty();
		glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		bool m_shouldDestroy{ false };

		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};

		std::vector<std::unique_ptr<ObjectComponent>> m_pComponents{};

		std::weak_ptr<GameObject> m_pParent{};
		std::vector<std::shared_ptr<GameObject>> m_pChildren{};
	};
}
