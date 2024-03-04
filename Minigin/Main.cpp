#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotatingComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent(std::make_unique<TextureComponent>(go, "background.tga"));
	scene.Add(go);

	/*go = std::make_shared<dae::GameObject>();
	go->AddComponent(std::make_shared<TextureComponent>(go.get(), "logo.tga"));
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	to->AddComponent(std::make_shared<dae::TextComponent>(to.get(), "Programming 4 Assignment", font));
	to->SetLocalPosition(80, 30);
	scene.Add(to);

	to = std::make_shared<dae::GameObject>();
	to->AddComponent(std::make_shared<FPSComponent>(to.get()));
	scene.Add(to);

	auto rotatingObj = std::make_shared<dae::GameObject>();
	rotatingObj->AddComponent(std::make_shared<TextureComponent>(rotatingObj.get(), "Diamond.png"));
	rotatingObj->SetLocalPosition(glm::vec3(50, 90, 0));
	rotatingObj->AddComponent(std::make_shared<RotatingComponent>(rotatingObj.get()));*/

	/*auto rotatingObj2 = std::make_shared<dae::GameObject>();
	rotatingObj2->AddComponent(std::make_shared<TextureComponent>("MoneyBag.png"));
	rotatingObj2->AddComponent(std::make_shared<RotatingComponent>(rotatingObj2.get()));

	rotatingObj2->SetParent(rotatingObj.get());*/

	//scene.Add(rotatingObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}