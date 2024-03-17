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
#include "GraphSteps.h"
#include "Command.h"
#include "InputManager.h"
#include "GamePad.h"
#include "InputComponents.h"

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

	/*to = std::make_shared<dae::GameObject>();
	auto graph = std::make_unique<GraphSteps>(to);
	to->AddComponent<GraphSteps>(graph);
	scene.Add(to);*/

	auto walkObj = std::make_shared<dae::GameObject>();

	float walkSpeed1{ .25f };
	auto walkPos = std::make_unique<Walk>(walkObj, walkSpeed1);
	auto walkNeg = std::make_unique<Walk>(walkObj, -walkSpeed1);

	std::unique_ptr<Command> walkCommandHorPos1 =  std::make_unique<WalkCommandHorizontal>(walkPos.get());
	std::unique_ptr<Command> walkCommandHorNeg1 =  std::make_unique<WalkCommandHorizontal>(walkNeg.get());
	std::unique_ptr<Command> walkCommandVertPos1 = std::make_unique<WalkCommandVertical>  (walkPos.get());
	std::unique_ptr<Command> walkCommandVertNeg1 = std::make_unique<WalkCommandVertical>  (walkNeg.get());

	walkObj->AddComponent(walkPos);
	walkObj->AddComponent(walkNeg);

	auto diamondTexture = std::make_unique<TextureComponent>(walkObj, "Diamond.png");
	walkObj->AddComponent<TextureComponent>(diamondTexture);

	walkCommandHorPos1->BindCommand(XINPUT_GAMEPAD_DPAD_RIGHT);
	walkCommandHorNeg1->BindCommand(XINPUT_GAMEPAD_DPAD_LEFT);
	walkCommandVertPos1->BindCommand(XINPUT_GAMEPAD_DPAD_DOWN);
	walkCommandVertNeg1->BindCommand(XINPUT_GAMEPAD_DPAD_UP);

	auto& IM = dae::InputManager::GetInstance();
	IM.AddCommand(walkCommandHorPos1);
	IM.AddCommand(walkCommandHorNeg1);
	IM.AddCommand(walkCommandVertPos1);
	IM.AddCommand(walkCommandVertNeg1);
	
	scene.Add(walkObj);

	auto walkObj2 = std::make_shared<dae::GameObject>();

	float walkSpeed2{ walkSpeed1 / 2 };
	auto walkPos2 = std::make_unique<Walk>(walkObj2, walkSpeed2);
	auto walkNeg2 = std::make_unique<Walk>(walkObj2, -walkSpeed2);

	std::unique_ptr<Command> walkCommandHorPos2 =  std::make_unique<WalkCommandHorizontal>(walkPos2.get());
	std::unique_ptr<Command> walkCommandHorNeg2 =  std::make_unique<WalkCommandHorizontal>(walkNeg2.get());
	std::unique_ptr<Command> walkCommandVertPos2 = std::make_unique<WalkCommandVertical>  (walkPos2.get());
	std::unique_ptr<Command> walkCommandVertNeg2 = std::make_unique<WalkCommandVertical>  (walkNeg2.get());

	walkObj2->AddComponent(walkPos2);
	walkObj2->AddComponent(walkNeg2);

	auto moneyTexture = std::make_unique<TextureComponent>(walkObj2, "MoneyBag.png");
	walkObj2->AddComponent<TextureComponent>(moneyTexture);

	walkCommandHorPos2->BindCommand(SDL_SCANCODE_D, SDL_PRESSED);
	walkCommandHorNeg2->BindCommand(SDL_SCANCODE_A, SDL_PRESSED);
	walkCommandVertPos2->BindCommand(SDL_SCANCODE_S, SDL_PRESSED);
	walkCommandVertNeg2->BindCommand(SDL_SCANCODE_W, SDL_PRESSED);

	walkCommandHorPos2->BindCommand(SDL_SCANCODE_RIGHT, SDL_PRESSED);
	walkCommandHorNeg2->BindCommand(SDL_SCANCODE_LEFT, SDL_PRESSED);
	walkCommandVertPos2->BindCommand(SDL_SCANCODE_DOWN, SDL_PRESSED);
	walkCommandVertNeg2->BindCommand(SDL_SCANCODE_UP, SDL_PRESSED);

	IM.AddCommand(walkCommandHorPos2);
	IM.AddCommand(walkCommandHorNeg2);
	IM.AddCommand(walkCommandVertPos2);
	IM.AddCommand(walkCommandVertNeg2);

	scene.Add(walkObj2);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}