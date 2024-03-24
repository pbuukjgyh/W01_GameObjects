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
#include "Observer Classes.h"

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

	auto font2 = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto instructionObj = std::make_shared<dae::GameObject>();
	auto instructionObj2 = std::make_shared<dae::GameObject>();
	auto instructions = std::make_unique<dae::TextComponent>(instructionObj, "Use WASD or arrows to move moneyBag, C to infict damage", font2);
	auto instructions2 = std::make_unique<dae::TextComponent>(instructionObj2, "Use D-pad to move cart, X to infictDamage", font2);
	instructionObj->AddComponent(instructions);
	instructionObj2->AddComponent(instructions2);

	instructionObj->SetLocalPosition(0, 75);
	instructionObj2->SetLocalPosition(0, 95);

	instructionObj2->SetParent(instructionObj.get(),false);

	scene.Add(instructionObj);

	/*to = std::make_shared<dae::GameObject>();
	auto graph = std::make_unique<GraphSteps>(to);
	to->AddComponent<GraphSteps>(graph);
	scene.Add(to);*/

	auto walkObj = std::make_shared<dae::GameObject>();

	int numLives{ 3 };

	auto health = std::make_unique<Health>(walkObj,numLives);
	walkObj->AddComponent(health);

	float walkSpeed1{ .25f };

	std::unique_ptr<Command> walkCommandHorPos1 =  std::make_unique<WalkCommand>(walkObj,glm::vec3{1,0,0} ,walkSpeed1);
	std::unique_ptr<Command> walkCommandHorNeg1 =  std::make_unique<WalkCommand>(walkObj,glm::vec3{-1,0,0},walkSpeed1);
	std::unique_ptr<Command> walkCommandVertPos1 = std::make_unique<WalkCommand>(walkObj,glm::vec3{0,1,0} ,walkSpeed1);
	std::unique_ptr<Command> walkCommandVertNeg1 = std::make_unique<WalkCommand>(walkObj,glm::vec3{0,-1,0},walkSpeed1);

	std::unique_ptr<Command> hurtCommand1 = std::make_unique<HurtCommand>(walkObj);

	auto cartTexture = std::make_unique<TextureComponent>(walkObj, "Cart.png");
	walkObj->AddComponent<TextureComponent>(cartTexture);

	auto displayHealthObj = std::make_shared<dae::GameObject>();
	auto displayHealth = std::make_unique<dae::TextComponent>(displayHealthObj, "# lives: "+ std::to_string(numLives), font2);
	displayHealthObj->AddComponent(displayHealth);
	displayHealthObj->SetLocalPosition(0, 215);

	std::shared_ptr<Observer> healthCommand = std::make_shared<RemainingLivesDisplay>(displayHealthObj.get());
	walkObj->AddObserver(healthCommand);

	scene.Add(displayHealthObj);

	walkObj->SetLocalPosition(150, 150);

	walkCommandHorPos1->BindCommand(XINPUT_GAMEPAD_DPAD_RIGHT);
	walkCommandHorNeg1->BindCommand(XINPUT_GAMEPAD_DPAD_LEFT);
	walkCommandVertPos1->BindCommand(XINPUT_GAMEPAD_DPAD_DOWN);
	walkCommandVertNeg1->BindCommand(XINPUT_GAMEPAD_DPAD_UP);

	hurtCommand1->BindCommand(XINPUT_GAMEPAD_X);

	auto& IM = dae::InputManager::GetInstance();
	IM.AddCommand(walkCommandHorPos1);
	IM.AddCommand(walkCommandHorNeg1);
	IM.AddCommand(walkCommandVertPos1);
	IM.AddCommand(walkCommandVertNeg1);

	IM.AddCommand(hurtCommand1);
	
	scene.Add(walkObj);

	auto walkObj2 = std::make_shared<dae::GameObject>();

	float walkSpeed2{ walkSpeed1 / 2 };

	std::unique_ptr<Command> walkCommandHorPos2  = std::make_unique<WalkCommand>(walkObj, glm::vec3{ 1,0 ,0}, walkSpeed2);
	std::unique_ptr<Command> walkCommandHorNeg2  = std::make_unique<WalkCommand>(walkObj, glm::vec3{ -1,0,0}, walkSpeed2);
	std::unique_ptr<Command> walkCommandVertPos2 = std::make_unique<WalkCommand>(walkObj, glm::vec3{ 0,1 ,0}, walkSpeed2);
	std::unique_ptr<Command> walkCommandVertNeg2 = std::make_unique<WalkCommand>(walkObj, glm::vec3{ 0,-1,0} , walkSpeed2);

	std::unique_ptr<Command> hurtCommand2 = std::make_unique<HurtCommand>(walkObj2);

	auto moneyTexture = std::make_unique<TextureComponent>(walkObj2, "MoneyBag.png");
	walkObj2->AddComponent<TextureComponent>(moneyTexture);

	walkObj2->SetLocalPosition(100, 150);

	auto displayHealthObj2 = std::make_shared<dae::GameObject>();
	auto displayHealth2 = std::make_unique<dae::TextComponent>(displayHealthObj2, "# lives: " + std::to_string(numLives), font2);
	displayHealthObj2->AddComponent(displayHealth2);
	displayHealthObj2->SetLocalPosition(0, 235);

	walkCommandHorPos2->BindCommand(SDL_SCANCODE_D, SDL_PRESSED);
	walkCommandHorNeg2->BindCommand(SDL_SCANCODE_A, SDL_PRESSED);
	walkCommandVertPos2->BindCommand(SDL_SCANCODE_S, SDL_PRESSED);
	walkCommandVertNeg2->BindCommand(SDL_SCANCODE_W, SDL_PRESSED);

	walkCommandHorPos2->BindCommand(SDL_SCANCODE_RIGHT, SDL_PRESSED);
	walkCommandHorNeg2->BindCommand(SDL_SCANCODE_LEFT, SDL_PRESSED);
	walkCommandVertPos2->BindCommand(SDL_SCANCODE_DOWN, SDL_PRESSED);
	walkCommandVertNeg2->BindCommand(SDL_SCANCODE_UP, SDL_PRESSED);

	hurtCommand2->BindCommand(SDL_SCANCODE_C, SDL_PRESSED);

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