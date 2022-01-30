
#include <memory>

#include "Game/Asteroid.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain(sf::Vector2u WorldSize)
	:LevelBase(WorldSize)
{
}

LevelMain::~LevelMain()
{
}

void LevelMain::Initialise()
{
	LevelBase::Initialise();

	// Create and Initialise PlayerSpaceShip
	std::shared_ptr<GameObject> tPlayerShip = std::make_shared<PlayerSpaceShip>();
	this->AddObject(tPlayerShip);
	this->m_PlayerSpaceShip = std::static_pointer_cast<PlayerSpaceShip>(tPlayerShip);
	tPlayerShip->SetPosition(sf::Vector2f(200.0f, 100.0f));

	//Create and Initialise Asteroids
	sf::Vector2f tAsteroidPos(300.0f, 300.0f);
	for (unsigned i = 0; i < 10; i++)
	{
		std::shared_ptr<GameObject> tAsteroid = std::make_shared<Asteroid>();
		this->AddObject(tAsteroid);
		tAsteroid->SetPosition(tAsteroidPos);
		tAsteroidPos.x += 200.0f;
		dynamic_cast<Asteroid*>(tAsteroid.get())->SetCanMultiply(true, 2);
	}
}

void LevelMain::Update(float DeltaTime)
{
	LevelBase::Update(DeltaTime);
}

void LevelMain::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
 	if (this->m_PlayerSpaceShip.lock().get())
	{
		m_PlayerSpaceShip.lock()->HandleInput(Key, IsPressed);
	}
}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);
}
