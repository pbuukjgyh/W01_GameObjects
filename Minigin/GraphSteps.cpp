#include "GraphSteps.h"
#include <chrono>

#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_opengl3.h"
#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_sdl2.h"
#include "..\3rdParty\imgui-1.90.4\plot-master\imgui_plot.h"

GraphSteps::GraphSteps(std::shared_ptr<dae::GameObject>& pOwner):
	ObjectComponent(pOwner)
{
	m_arrInt.resize(sizeArr); 
	m_arrClass.resize(sizeArr);
}

void GraphSteps::Render() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	if (ImGui::Begin("Exersize 2"))
	{
		ImGui::InputInt("#  samples", &m_samples, 1, 100, 1);

		if (!m_isLoadingInt)
		{
			if (ImGui::Button("Trash the cache with int"))
			{
				m_isLoadingInt = true;
			}
			if (m_timesInt.size() > 0)
			{
				ImGui::PlotLines(" ", m_timesInt.data(), int(m_timesInt.size()), 0, NULL, FLT_MIN, FLT_MAX, ImVec2(0, 125));
			}
		}
		else ImGui::Text(m_waitText.c_str());
		if(!m_isLoadingClass)
		{
			if (ImGui::Button("Trash the cache with class"))
			{
				m_isLoadingClass = true;
			}
			if (m_timesClass.size() > 0)
			{
				ImGui::PlotLines(" ", m_timesClass.data(), int(m_timesClass.size()), 0, NULL, FLT_MIN, FLT_MAX, ImVec2(0, 125));
			}
		}
		else ImGui::Text(m_waitText.c_str());

		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GraphSteps::Update(float /*deltaTime*/)
{
	if (m_isLoadingInt)
	{
		CalculateLoopInt();
	}
	if (m_isLoadingClass)
	{
		CalculateLoopClass();
	}
}

void GraphSteps::CalculateLoopInt()
{
	static int times{};

	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < m_arrInt.size(); i += stepsize)
		{
			m_arrInt[i] *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();

		float elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 100.0f);

		m_timesInt.emplace_back(elapsedTime);
	}

	++times;

	if(times >= m_samples)
	{
		m_isLoadingInt = false;

		times = 0;
	}
}

void GraphSteps::CalculateLoopClass()
{
	static int times{};

	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < m_arrClass.size(); i += stepsize)
		{
			m_arrClass[i].Function();
		}
		auto end = std::chrono::high_resolution_clock::now();

		float elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 100.0f);

		m_timesClass.emplace_back(elapsedTime);
	}

	++times;

	if (times >= m_samples)
	{
		m_isLoadingClass = false;

		times = 0;
	}
}
