#include <SDL.h>
#include "InputManager.h"
#include "InputHandler.h"
#include "../imgui-1.90.4/backends/imgui_impl_sdl2.h"

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN  || e.type == SDL_KEYUP) {
			SDL_Scancode keycode = e.key.keysym.scancode;
			Uint8 keystate = e.type == SDL_KEYDOWN ? SDL_PRESSED : SDL_RELEASED;

			for (auto& command : m_pCommands)
			{
				command->ExecuteKeys(keycode,keystate);
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_pGamepad->ProcessInput();

	for (auto& command : m_pCommands)
	{
		command->ExecuteController(m_pGamepad);
	}

	return true;
}

void dae::InputManager::AddCommand(Command* command)
{
	m_pCommands.emplace_back(command);
}



