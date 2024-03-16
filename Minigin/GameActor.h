#pragma once
#include "GameObject.h"
#include <iostream>
#include "ObjectComponent.h"


//class GameActor
//{
//	std::shared_ptr<dae::GameObject> m_pOwner;
//
//protected:
//	std::shared_ptr<dae::GameObject> GetOwner() { return m_pOwner; }
//
//	GameActor(std::shared_ptr<dae::GameObject> pOwner) : m_pOwner{pOwner}{}
//};

class Walk : public ObjectComponent
{
public:
	Walk(std::shared_ptr<dae::GameObject> pOwner) : ObjectComponent(pOwner) {};

	void Step()
	{
		std::cout << "Step";
	}
};