#pragma once
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>
#include <Xinput.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		std::vector<Command*> m_commands{};
		std::unordered_map<SDL_Scancode, std::pair<Command*, Uint8>> m_keyBindings;

		std::unique_ptr<Gamepad> m_gamepad{std::make_unique<Gamepad>(0)};

		std::unordered_map<WORD, std::pair<std::unique_ptr<Command>, bool>> m_controllerBindings;

	public:
		bool ProcessInput();

		//void BindCommand(std::unique_ptr<Command>& command, SDL_Scancode keyCode, Uint8 downState);
		void BindCommand(Command* command, SDL_Scancode keyCode, Uint8 downState);
		void BindCommand(Command* command, WORD buttonCode, bool buttonState);
		//void AddCommand(Command* command) { m_commands.emplace_back(std::unique_ptr<Command>(command)); };
		//void BindContollerCommand(Command* command, XINPUT_GAMEPAD)
	};

}
