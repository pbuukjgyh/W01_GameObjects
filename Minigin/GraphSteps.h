#pragma once
#include <vector>
#include <string>
#include "Transform.h"
#include "ObjectComponent.h"

#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_opengl3.h"
#include "..\3rdParty\imgui-1.90.4\backends\imgui_impl_sdl2.h"
#include "..\3rdParty\imgui-1.90.4\plot-master\imgui_plot.h"

class TestObject
{
	dae::Transform* m_pLocal;
	int m_id;
public:
	void Function() { m_id *= 2; }
};

class GraphSteps : public ObjectComponent
{
public:
	GraphSteps(std::shared_ptr<dae::GameObject>& pOwner);
	~GraphSteps() = default;
	GraphSteps(const GraphSteps& copy) = delete;
	GraphSteps(GraphSteps&& move) = delete;
	GraphSteps& operator=(const GraphSteps& toCopy) = delete;
	GraphSteps& operator=(GraphSteps&& toMove) = delete;

	void Render() const;
	void Update(float deltaTime);

private:
	mutable int m_samples{ 2 };

	const int sizeArr{ 10000000 };

	std::vector<int> m_arrInt{};
	std::vector<TestObject> m_arrClass{};

	std::vector<long long> m_timesInt{};
	std::vector<long long> m_timesClass{};

	bool m_isLoadingInt{ false };
	bool m_isLoadingClass{ false };

	mutable bool m_startLoadingInt{ false };
	mutable bool m_startLoadingClass{ false };

	const std::string m_waitText{ "Wait for it..." };

	ImGui::PlotConfig m_plotInt{};
	ImGui::PlotConfig m_plotClass{};

	void CalculateLoopInt();
	void CalculateLoopClass();

};

