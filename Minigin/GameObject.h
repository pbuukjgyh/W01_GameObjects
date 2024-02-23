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

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void AddComponent(const std::shared_ptr<ObjectComponent>& newComponent);

		GameObject() = default;
		GameObject(const std::vector<std::shared_ptr<ObjectComponent>>& startComponents);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<ObjectComponent>> m_pComponents{};
	};
}
