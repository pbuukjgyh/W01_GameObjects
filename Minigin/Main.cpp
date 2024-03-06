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
	auto bgTexture = std::make_unique<TextureComponent>(go, "background.tga");
	go->AddComponent<TextureComponent>(bgTexture);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	auto logoTexture = std::make_unique<TextureComponent>(go, "logo.tga");
	go->AddComponent<TextureComponent>(logoTexture);
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::GameObject>();
	auto title = std::make_unique<dae::TextComponent>(to, "Programming 4 Assignment", font);
	to->AddComponent<dae::TextComponent>(title);
	to->SetLocalPosition(80, 30);
	scene.Add(to);

	to = std::make_shared<dae::GameObject>();
	auto fpsCounter = std::make_unique<FPSComponent>(to);
	to->AddComponent<FPSComponent>(fpsCounter);
	scene.Add(to);

	auto rotatingObj = std::make_shared<dae::GameObject>();
	auto diamondTexture = std::make_unique<TextureComponent>(rotatingObj, "Diamond.png");
	rotatingObj->AddComponent<TextureComponent>(diamondTexture);
	rotatingObj->SetLocalPosition(glm::vec3(50, 90, 0));
	auto rotation = std::make_unique<RotatingComponent>(rotatingObj);
	rotatingObj->AddComponent(rotation);

	auto rotatingObj2 = std::make_shared<dae::GameObject>();
	auto moneyTexture = std::make_unique<TextureComponent>(rotatingObj2, "MoneyBag.png");
	rotatingObj2->AddComponent<TextureComponent>(moneyTexture);
	auto rotation2 = std::make_unique<RotatingComponent>(rotatingObj2);
	rotatingObj2->AddComponent<RotatingComponent>(rotation2);

	rotatingObj2->SetParent(rotatingObj.get());

	scene.Add(rotatingObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}