#pragma once
#include <Windows.h>
#include <Xinput.h>

//Xinput
class Gamepad
{
	XINPUT_STATE m_previousState;
	XINPUT_STATE m_currentState;
	DWORD m_controllerIndex;

	DWORD m_buttonsPressedThisFrame;
	DWORD m_buttonsReleasedThisFrame;

	int cId{};
	XINPUT_STATE state{};

	float deadzoneX;
	float deadzoneY;

public:

	Gamepad(DWORD controllerIndex) : m_previousState{}, m_currentState{}, m_controllerIndex(controllerIndex), m_buttonsPressedThisFrame{}, m_buttonsReleasedThisFrame{}, deadzoneX(0.05f), deadzoneY(0.02f) {};

	~Gamepad() = default;
	Gamepad(const Gamepad& other) = delete;
	Gamepad(Gamepad&& other) = delete;
	Gamepad& operator=(const Gamepad& other) = delete;
	Gamepad& operator=(Gamepad&& other) = delete;

	float leftStickX{};
	float leftStickY{};
	float rightStickX{};
	float rightStickY{};
	float leftTrigger{};
	float rightTrigger{};

	int  GetPort();
	XINPUT_GAMEPAD* GetState();

	void ProcessInput();

	bool IsDownThisFrame(unsigned int button) const { return m_buttonsPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return m_buttonsReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return m_currentState.Gamepad.wButtons & button; }

};

