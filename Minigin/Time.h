#pragma once
#include <chrono>
#include "Singleton.h"

class Time : public dae::Singleton<Time>
{
public:
	float deltaTime{};
	std::chrono::steady_clock::time_point lastTime{};
	std::chrono::steady_clock::time_point currentTime{};
	std::chrono::nanoseconds passingTime{};
	std::chrono::nanoseconds sleepTime{};
};