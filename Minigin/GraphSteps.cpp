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

	m_plotInt.frame_size = { 250,125 };
	m_plotClass.frame_size = m_plotInt.frame_size;
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
				m_startLoadingInt = true;
			}
			if (m_timesInt.size() > 0)
			{
				ImGui::Plot(" ", m_plotInt);
			}
		}
		else ImGui::Text(m_waitText.c_str());
		if(!m_isLoadingClass)
		{
			if (ImGui::Button("Trash the cache with class"))
			{
				m_startLoadingClass = true;
			}
			if (m_timesClass.size() > 0)
			{
				ImGui::Plot(" ", m_plotClass);
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
		m_timesInt.clear();

		m_startLoadingInt = false;
		m_isLoadingInt = true;

		CalculateLoopInt();
	}
	if (m_startLoadingClass)
	{
		m_timesClass.clear();

		m_startLoadingClass = false;
		m_isLoadingClass = true;

		CalculateLoopClass();
	}
}

void GraphSteps::CalculateLoopInt()
{
	for(int times{}; times < m_samples; ++times)
	{
		//for (int step{ 1 }; step <= 1024; step *= 2)
		{
			for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < m_arrInt.size(); i += stepsize)
				{
					m_arrInt[i] *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();
				auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				m_timesInt.emplace_back(elapsedTime);
			}
		}
	}

	m_isLoadingInt = false;
}

void GraphSteps::CalculateLoopClass()
{
	for (int times{}; times < m_samples; ++times)
	{
		//for (int step{ 1 }; step <= 1024; step *= 2)
		{
			for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < m_arrClass.size(); i += stepsize)
				{
					m_arrClass[i].Function();
				}
				auto end = std::chrono::high_resolution_clock::now();
				auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				m_timesClass.emplace_back(elapsedTime);
			}
		}
	}

	m_isLoadingClass = false;
}
