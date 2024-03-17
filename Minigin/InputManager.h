#pragma once
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>
#include <Xinput.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		std::vector<std::unique_ptr<Command>> m_pCommands{};
		std::unordered_map<SDL_Scancode, std::pair<Command*, Uint8>> m_keyBindings;

		std::unique_ptr<Gamepad> m_pGamepad{std::make_unique<Gamepad>(0)};

		std::unordered_map<WORD, std::pair<std::unique_ptr<Command>, bool>> m_controllerBindings;

	public:
		bool ProcessInput();

		//we set ownership to the commands
		void AddCommand(std::unique_ptr<Command>& command);
	};

}
