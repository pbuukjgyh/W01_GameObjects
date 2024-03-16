#pragma once
#include "Command.h"

class InputHandler
{
public:
	void BindCommand(Command* command, int keyCode, bool downState);

	void ProcessInput();
};

//Xinput
class Gamepad 
{
	XINPUT_STATE m_previousState;
	XINPUT_STATE m_currentState;
	DWORD m_controllerIndex;

	DWORD m_buttonsPressedThisFrame;
	DWORD m_buttonsReleasedThisFrame;
public:

	Gamepad(DWORD controllerIndex) : m_previousState{}, m_currentState{}, m_controllerIndex(controllerIndex), m_buttonsPressedThisFrame{}, m_buttonsReleasedThisFrame{} {};

	void ProcessInput();

	bool IsDownThisFrame(unsigned int button) const { return m_buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_currentState.Gamepad.wButtons & button; }

};

