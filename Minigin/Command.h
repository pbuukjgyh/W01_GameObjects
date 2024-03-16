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
	// std::vector<XINPUT_STATE> m_controllerStates{};
	// std::vector<std::pair<SDL_KeyboardEvent,Uint8>> m_keyStates{};
public:
	std::pair<int, bool> m_state;
	WORD m_stateController;

	virtual ~Command() = default;
	virtual void Execute() = 0;
};

#include "InputHandler.h"
#include <iostream>
#include "GameActor.h"

class GameActorCommand : public Command
{
private:
	ObjectComponent* m_pActor;
protected:
	ObjectComponent* GetComponent() const { return m_pActor; }
public:
	GameActorCommand(ObjectComponent* pActor) :
		m_pActor{pActor} {};

	virtual ~GameActorCommand() { delete m_pActor; };
	virtual void Execute() override = 0;
};

class WalkCommand : public GameActorCommand
{
	Walk* m_pWalk;
public:
	WalkCommand(Walk* pWalk) : GameActorCommand(pWalk) 
	{ 
		m_pWalk = pWalk; 
	}

	virtual ~WalkCommand() { delete m_pWalk; };

	void Execute() override { m_pWalk->Step(); };
};
