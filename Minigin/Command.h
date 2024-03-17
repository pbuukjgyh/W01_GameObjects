#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <XInput.h>
#include "ObjectComponent.h"
#include <SDL_stdinc.h>
#include <SDL.h>
#include "GamePad.h"
#include "ControllerPimpl.h"

class Command abstract
{
	std::vector<std::pair<SDL_Scancode, Uint8>> m_statesKeys;
	std::vector<ControllerInput> m_statesController;
public:
	void BindCommand(SDL_Scancode keyCode, Uint8 downState);
	void BindCommand(unsigned int buttonCode);

	void ExecuteController(const std::unique_ptr<Gamepad>& pGamepad);
	void ExecuteKeys(SDL_Scancode currentKeycode, Uint8 currentKeystate);

	Command() = default;
	virtual ~Command() = default;

protected:
	virtual void Execute() = 0;
};

#include <iostream>
#include "InputComponents.h"

class GameActorCommand abstract : public Command
{
private:
	ObjectComponent* m_pActor;
protected:
	ObjectComponent* GetComponent() const { return m_pActor; }
public:
	GameActorCommand(ObjectComponent* pActor) :
		m_pActor{pActor} {};

	virtual ~GameActorCommand() = default;
	virtual void Execute() override = 0;
};

class WalkCommandHorizontal : public GameActorCommand
{
protected:
	Walk* m_pWalk;
public:
	WalkCommandHorizontal(Walk* pWalk) : GameActorCommand(pWalk)
	{ 
		m_pWalk = pWalk; 
	}

	virtual ~WalkCommandHorizontal() = default;

	virtual void Execute() override { m_pWalk->StepHorizontal(); };
};

class WalkCommandVertical : public WalkCommandHorizontal
{
public:
	WalkCommandVertical(Walk* pWalk) : WalkCommandHorizontal(pWalk) {}

	virtual void Execute() override { m_pWalk->StepVertical(); };
};
