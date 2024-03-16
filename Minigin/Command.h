#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <XInput.h>
#include "ObjectComponent.h"
#include <SDL_stdinc.h>
#include <SDL.h>
#include "GameObject.h"

class Command 
{
protected:
	/*std::vector<XINPUT_STATE> m_controllerStates{};
	std::vector<std::pair<SDL_KeyboardEvent,Uint8>> m_keyStates{};*/
public:
	std::pair<int, bool> m_state;

	virtual ~Command() = default;
	virtual void Execute() = 0;
};

#include "InputHandler.h"

class GameActorCommand : public Command
{
	std::unique_ptr<ObjectComponent> m_pComponent;
protected:
	ObjectComponent* GetComponent() const { return m_pComponent.get(); }
public:
	GameActorCommand(ObjectComponent* pActor) : 
		m_pComponent{ std::unique_ptr<ObjectComponent>(pActor)} {};

	virtual ~GameActorCommand() = default;
	virtual void Execute() override = 0;
};

class Walk : public ObjectComponent
{
public:
	Walk(std::shared_ptr<dae::GameObject>& pOwner): ObjectComponent(pOwner) {};

	void Step()
	{
		auto pos{ this->getOwnerPos() };

		SetPosition(pos.x + 1, pos.y);
	}
};

class WalkCommand : public GameActorCommand
{
	Walk* m_pWalk;
public:
	WalkCommand(Walk* pWalk) : GameActorCommand(pWalk) 
	{ 
		m_pWalk = pWalk; 
	}

	void Execute() override { m_pWalk->Step(); };
};
