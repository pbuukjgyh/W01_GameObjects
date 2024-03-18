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

#include "Time.h"

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

class GameActorCommand abstract : public Command
{
private:
	std::shared_ptr<dae::GameObject> m_pOwner;
protected:
	dae::GameObject* GetOwner() const { return m_pOwner.get(); }
public:
	GameActorCommand(std::shared_ptr<dae::GameObject> pOwner) :
		m_pOwner{pOwner} {};

	virtual ~GameActorCommand() = default;

	GameActorCommand(const GameActorCommand& other) = delete;
	GameActorCommand(GameActorCommand&& other) = delete;
	GameActorCommand& operator=(const GameActorCommand& other) = delete;
	GameActorCommand& operator=(GameActorCommand&& other) = delete;

	virtual void Execute() override = 0;
};

class WalkCommand : public GameActorCommand
{
	glm::vec3 m_direction;
	float m_speed{ .5f };
public:
	WalkCommand(std::shared_ptr<dae::GameObject>& pOwner, const glm::vec3& direction) : GameActorCommand(pOwner) { m_direction = direction; }
	WalkCommand(std::shared_ptr<dae::GameObject>& pOwner, const glm::vec3& direction, float speed) : WalkCommand(pOwner, direction) { m_speed = speed; }

	virtual ~WalkCommand() = default;

	WalkCommand(const WalkCommand& other) = delete;
	WalkCommand(WalkCommand&& other) = delete;
	WalkCommand& operator=(const WalkCommand& other) = delete;
	WalkCommand& operator=(WalkCommand&& other) = delete;

	virtual void Execute() override 
	{ 
		auto pos{ GetOwner()->GetWorldPosition()};
		pos += m_direction * m_speed * Time::GetInstance().deltaTime;
		GetOwner()->SetLocalPosition(pos);
	};
};
