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

	m_combinedPlot.frame_size = m_intVar.plot.frame_size;
	m_combinedPlot.tooltip.show = true;
	m_combinedPlot.grid_x.size = 1.0f;
	m_combinedPlot.tooltip.format = "x=%.2f, y=%.2f";

	m_combinedPlot.values.ys_list = new const float* [2];

	ImU32 colors[2]{ ImColor(155, 255, 0), ImColor(255, 155, 0) };
	m_combinedPlot.values.colors = colors;

	m_intVar.plot.values.color = colors[1];
	m_classVar.plot.values.color = colors[1];
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
				ImGui::Plot(" ", m_intVar.plot);
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
				//ImGui::PlotLines(" ", m_classVar.times.data(), int(m_classVar.times.size()), 0, NULL, FLT_MIN, FLT_MAX, ImVec2(0, 80));
				ImGui::Plot(" ", m_classVar.plot);
			}
		}
		else ImGui::Text(m_waitText.c_str());

		if (m_classVar.samples == m_intVar.samples && m_intVar.times.size() != 0 && m_classVar.times.size() != 0)
		{
			ImGui::Text("combined:");
			ImGui::Plot(" ", m_combinedPlot);
		}

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

	++m_intVar.samples;

	if(m_intVar.samples >= m_samples)
	{
		m_intVar.AvrageTimes();

		m_intVar.Reset();

		SetCombined();
	}
}

void GraphSteps::CalculateLoopClass()
{
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

	++m_classVar.samples;

	if (m_classVar.samples >= m_samples)
	{
		m_classVar.AvrageTimes();

		m_classVar.Reset();

		SetCombined();
	}
}

void GraphSteps::SetCombined()
{
	if(m_intVar.times.size() != 0 && m_classVar.times.size() != 0)
	{
		m_combinedPlot.values.ys_list[0] = m_intVar.times.data();
		m_combinedPlot.values.ys_list[1] = m_classVar.times.data();

		m_combinedPlot.values.ys_count = 2;
		m_combinedPlot.values.count = int(m_intVar.times.size());
		m_combinedPlot.scale.min = 0;
		m_combinedPlot.scale.max = std::max(m_intVar.times[m_intVar.times.size() - 1], m_classVar.times[m_classVar.times.size() - 1]);
	}
}
