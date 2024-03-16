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
		if (e.type == SDL_KEYDOWN /* || e.type == SDL_KEYUP*/) {
			SDL_Scancode keycode = e.key.keysym.scancode;
			Uint8 keystate = e.type == SDL_KEYDOWN ? SDL_PRESSED : SDL_RELEASED;

			auto it = m_keyBindings.find(keycode);
			if (it != m_keyBindings.end() && it->second.second == keystate)
			{
				it->second.first->Execute();
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	/*for (auto& command : m_commands)
	{
		if (command->m_state.second)
		{
			command->Execute();
		}
	}*/

	m_gamepad->ProcessInput();

	/*for (auto& controllerBinding : m_controllerBindings)
	{
		if (m_gamepad->IsDownThisFrame(controllerBinding.first))
		{
			controllerBinding.second.first->Execute();
		}
	}*/
	for (auto& command : m_commands)
	{
		if (m_gamepad->IsDownThisFrame(command->m_stateController))
		{
			command->Execute();
		}
	}

	return true;
}

void dae::InputManager::BindCommand(Command* command, SDL_Scancode keyCode, Uint8 downState)
{
	//command->m_state = { keyCode, downState };
	m_keyBindings[keyCode] = std::make_pair(std::move(command), downState);
}

void dae::InputManager::BindCommand(Command* command, WORD buttonCode, bool /*buttonState*/)
{
	//m_controllerBindings[buttonCode] = std::make_pair(std::move(command), buttonState);
	command->m_stateController = buttonCode;
	m_commands.push_back(command);
}



