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

		if (!m_intVar.isLoading)
		{
			if (ImGui::Button("Trash the cache with int"))
			{
				m_intVar.isLoading = true;

				m_intVar.shouldReset = true;
			}
			if (m_intVar.times.size() > 0)
			{
				ImGui::PlotLines(" ", m_intVar.times.data(), int(m_intVar.times.size()), 0, NULL, FLT_MIN, FLT_MAX, ImVec2(0, 125));
			}
		}
		else ImGui::Text(m_waitText.c_str());
		if(!m_classVar.isLoading)
		{
			if (ImGui::Button("Trash the cache with class"))
			{
				m_classVar.isLoading = true;

				m_classVar.shouldReset = true;
			}
			if (m_classVar.times.size() > 0)
			{
				ImGui::PlotLines(" ", m_classVar.times.data(), int(m_classVar.times.size()), 0, NULL, FLT_MIN, FLT_MAX, ImVec2(0, 125));
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
	if (m_intVar.ShouldUpdate())
	{
		CalculateLoopInt();
	}
	if (m_classVar.ShouldUpdate())
	{
		CalculateLoopClass();
	}
}

void GraphSteps::CalculateLoopInt()
{
	static int time{};

	for (int stepsize{ 1 }; stepsize <= 1024; stepsize *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < m_arrInt.size(); i += stepsize)
		{
			m_arrInt[i] *= 2;
		}
		auto end = std::chrono::high_resolution_clock::now();

		float elapsedTime = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 100.0f);

		m_intVar.times.emplace_back(elapsedTime);
	}

	++time;

	if(time >= m_samples)
	{
		const int amountInTimes{ int(log2(1024))+1 };
		for (int index = amountInTimes; index < m_intVar.times.size(); ++index)
		{
			m_intVar.times[index % amountInTimes] += m_intVar.times[index];
		}

		m_intVar.times.resize(amountInTimes);

		for (int index = 0; index < m_intVar.times.size(); ++index)
		{
			m_intVar.times[index] /= amountInTimes;
		}

		m_intVar.isLoading = false;

		time = 0;
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

		m_classVar.times.emplace_back(elapsedTime);
	}

	++times;

	if (times >= m_samples)
	{
		m_classVar.isLoading = false;

		times = 0;
	}
}
