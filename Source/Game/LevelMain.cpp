
#include "Game/PlayerSpaceShip.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain()
{
}

LevelMain::~LevelMain()
{
}

void LevelMain::Initialize()
{
	LevelBase::Initialize();

	std::shared_ptr<GameObject> PlayerShip = std::make_shared<PlayerSpaceship>();
	this->AddObject(PlayerShip);
	PlayerShip->Initialise();
}

void LevelMain::Update(float DeltaTime)
{
	LevelBase::Update(DeltaTime);
}

void LevelMain::HandleEvent(sf::Event Event)
{
	LevelBase::HandleEvent(Event);
}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);
}