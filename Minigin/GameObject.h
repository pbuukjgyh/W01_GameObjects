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
		void AddComponent(ObjectComponent* pNewComponent);
		//Removes all components of type
		template <typename T>
		void RemoveComponents()
		{
			//sets all removable components to the back and then makes erase erase all comps in the back
			m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(),
				[](const std::shared_ptr<ObjectComponent>& comp)
				{
					return dynamic_cast<T*>(comp.get()) != nullptr;
				}), m_pComponents.end());
		}
		//returns vector of all the types
		template <typename T>
		std::vector<std::shared_ptr<T>> GetComponents()
		{
			std::vector<std::shared_ptr<T>> components;
			for (const auto& pComp : m_pComponents) {
				if (std::shared_ptr<T> pDerived = std::dynamic_pointer_cast<T>(pComp)) 
				{
					components.push_back(pDerived);
				}
			}
			return components;
		}
		//returns the first of a type
		template <typename T>
		std::shared_ptr<T> GetComponent()
		{
			std::vector<std::shared_ptr<T>> components;
			for (const auto& pComp : m_pComponents) {
				if (std::shared_ptr<T> pDerived = std::dynamic_pointer_cast<T>(pComp))
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
		template <typename T>
		bool HasComponent(T pComponent)
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(),
				[pComponent](const std::shared_ptr<ObjectComponent>& p) {
					return p.get() == pComponent;
				});
			return it != m_pComponents.end();
		}

		glm::vec3 GetPosition() const { return m_transform.GetPosition(); };

		GameObject();
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
