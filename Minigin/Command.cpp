#include "Command.h"

void Command::BindCommand(SDL_Scancode keyCode, Uint8 downState)
{
	m_statesKeys.emplace_back(std::pair{ keyCode, downState });
}

void Command::BindCommand(unsigned int buttonCode)
{
	ControllerInput state{ buttonCode };
	m_statesController.emplace_back(state);
}

void Command::ExecuteController(const std::unique_ptr<Gamepad>& pGamepad)
{
	for (auto& controllerState : m_statesController)
	{
		if (pGamepad->IsPressed(controllerState.GetButton()))
		{
			Execute();
		}
	}
}

void Command::ExecuteKeys(SDL_Scancode currentKeycode, Uint8 currentKeystate)
{
	for (auto& keyState : m_statesKeys)
	{
		if (keyState.first == currentKeycode && keyState.second == currentKeystate)
		{
			Execute();
		}
	}
}
