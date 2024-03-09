#include "GraphSteps.h"
#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_opengl3.h"
#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_sdl2.h"
#include <chrono>

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
				m_startLoadingInt = true;
			}
		}
		else ImGui::Text(m_waitText.c_str());
		if(!m_isLoadingClass)
		{
			if (ImGui::Button("Trash the cache with class"))
			{
				m_startLoadingClass = true;
			}
		}
		else ImGui::Text(m_waitText.c_str());

		ImGui::End();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GraphSteps::Update(float)
{
	if (m_startLoadingInt)
	{
		m_startLoadingInt = false;
		m_isLoadingInt = true;
	}
	if (m_startLoadingClass)
	{
		m_startLoadingClass = false;
		m_isLoadingClass = true;
	}
}

void GraphSteps::CalculateLoopInt()
{
	for (int step{1}; step <= 1024; step *= 2)
	{
		for (int stepsize{ step }; stepsize <= 1024; stepsize *= 2)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < m_arrInt.size(); i += stepsize)
			{
				m_arrInt[i] *= 2;
			}
			auto end = std::chrono::high_resolution_clock::now();
			//auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		}
	}
}
