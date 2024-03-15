#pragma once
#include <memory>
#include <vector>
#include "Xinput.h"
#include "ObjectComponent.h"

class Command 
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};

class GameActorCommand : public Command
{
	std::unique_ptr<ObjectComponent> m_pComponent;
protected:
	ObjectComponent* GetComponent() const { return m_pComponent.get(); }
public:
	GameActorCommand(ObjectComponent* pActor) : m_pComponent{ std::make_unique<ObjectComponent>(pActor)} {};
	virtual ~GameActorCommand() = default;
	virtual void Execute() override = 0;
};