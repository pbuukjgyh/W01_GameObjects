#pragma once
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>
#include <Xinput.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		std::vector<std::unique_ptr<Command>> m_commands{};
		std::unordered_map<SDL_Scancode, std::pair<std::unique_ptr<Command>, Uint8>> m_keyBindings;

	public:
		bool ProcessInput();

		void BindCommand(std::unique_ptr<Command>& command, SDL_Scancode keyCode, Uint8 downState);
		//void AddCommand(Command* command) { m_commands.emplace_back(std::unique_ptr<Command>(command)); };
		//void BindContollerCommand(Command* command, XINPUT_GAMEPAD)
	};

}
