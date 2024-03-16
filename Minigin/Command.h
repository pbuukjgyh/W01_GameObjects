#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <XInput.h>
#include "ObjectComponent.h"
#include <SDL_stdinc.h>
#include <SDL.h>

class Command 
{
protected:
	std::vector<XINPUT_STATE> m_controllerStates{};
	std::vector<std::pair<SDL_KeyboardEvent,Uint8>> m_keyStates{};
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
	GameActorCommand(ObjectComponent* pActor) : m_pComponent{ std::unique_ptr<ObjectComponent>(pActor)} {};
	virtual ~GameActorCommand() = default;
	virtual void Execute() override = 0;
};