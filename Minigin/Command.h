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

	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;

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

	GameActorCommand(const GameActorCommand& other) = delete;
	GameActorCommand(GameActorCommand&& other) = delete;
	GameActorCommand& operator=(const GameActorCommand& other) = delete;
	GameActorCommand& operator=(GameActorCommand&& other) = delete;

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

	WalkCommandHorizontal(const WalkCommandHorizontal& other) = delete;
	WalkCommandHorizontal(WalkCommandHorizontal&& other) = delete;
	WalkCommandHorizontal& operator=(const WalkCommandHorizontal& other) = delete;
	WalkCommandHorizontal& operator=(WalkCommandHorizontal&& other) = delete;

	virtual void Execute() override { m_pWalk->StepHorizontal(); };
};

class WalkCommandVertical : public WalkCommandHorizontal
{
public:
	WalkCommandVertical(Walk* pWalk) : WalkCommandHorizontal(pWalk) {}

	virtual ~WalkCommandVertical() = default;

	WalkCommandVertical(const WalkCommandVertical& other) = delete;
	WalkCommandVertical(WalkCommandVertical&& other) = delete;
	WalkCommandVertical& operator=(const WalkCommandVertical& other) = delete;
	WalkCommandVertical& operator=(WalkCommandVertical&& other) = delete;

	virtual void Execute() override { m_pWalk->StepVertical(); };
};
