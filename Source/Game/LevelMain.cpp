
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

	std::shared_ptr<GameObject> PlayerShip = std::make_shared<PlayerSpaceShip>();
	this->AddObject(PlayerShip);

	this->m_PlayerSpaceShip = static_cast<PlayerSpaceShip*>(PlayerShip.get());

	PlayerShip->Initialise();
}

void LevelMain::Update(float DeltaTime)
{
	LevelBase::Update(DeltaTime);
}

void LevelMain::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
	this->m_PlayerSpaceShip->HandleInput(Key, IsPressed);
}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);
}