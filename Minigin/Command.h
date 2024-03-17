#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <XInput.h>
#include "ObjectComponent.h"
#include <SDL_stdinc.h>
#include <SDL.h>
#include "InputHandler.h"

class Command
{
	std::vector<std::pair<SDL_Scancode, Uint8>> m_statesKeys;
	std::vector<WORD> m_statesController;
public:
	void BindCommand(SDL_Scancode keyCode, Uint8 downState);
	void BindCommand(WORD buttonCode);

	void ExecuteController(const std::unique_ptr<Gamepad>& pGamepad);
	void ExecuteKeys(SDL_Scancode currentKeycode, Uint8 currentKeystate);

	Command() = default;
	virtual ~Command() = default;

protected:
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
