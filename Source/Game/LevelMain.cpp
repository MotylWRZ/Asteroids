
#include "Game/PlayerSpaceShip.h"
#include "Game/Asteroid.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain(sf::Vector2u WorldSize)
	:LevelBase(WorldSize)
	,m_PlayerSpaceShip(nullptr)
{
}

LevelMain::~LevelMain()
{
}

void LevelMain::Initialize()
{
	LevelBase::Initialize();

	// Create and Initialise PlayerSpaceShip
	std::shared_ptr<GameObject> tPlayerShip = std::make_shared<PlayerSpaceShip>();
	this->AddObject(tPlayerShip);
	this->m_PlayerSpaceShip = static_cast<PlayerSpaceShip*>(tPlayerShip.get());

	tPlayerShip->SetPosition(sf::Vector2f(200.0f, 100.0f));
	tPlayerShip->Initialise();


	//Create and Initialise Asteroids
	sf::Vector2f tAsteroidPos(300.0f, 300.0f);
	for (unsigned i = 0; i < 3; i++)
	{
		std::shared_ptr<GameObject> tAsteroid = std::make_shared<Asteroid>();
		this->AddObject(tAsteroid);
		tAsteroid->SetPosition(tAsteroidPos);
		tAsteroidPos.x += 200.0f;
		tAsteroid->Initialise();
	}

}

void LevelMain::Update(float DeltaTime)
{
	for (auto& tGameObject : this->GetObjectsRef())
	{
		if (!tGameObject)
		{
			continue;
		}

		tGameObject->Update(DeltaTime);

		if (this->m_WorldSize.x != 0 && this->m_WorldSize.y != 0)
		{
			this->WrapObjectCoordinates(tGameObject.get());
		}
	}
}

void LevelMain::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
	this->m_PlayerSpaceShip->HandleInput(Key, IsPressed);
}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);
}

void LevelMain::WrapObjectCoordinates(GameObject* Object)
{
	sf::Vector2f tObjectPos = Object->GetPosition();

	// Wrap the X coordinate
	if (tObjectPos.x < 0.0f)
	{
		tObjectPos.x = this->m_WorldSize.x;
	}
	else if (tObjectPos.x > this->m_WorldSize.x)
	{
		tObjectPos.x = 0.0f;
	}

	// Wrap Y coordinate
	if (tObjectPos.y < 0.0f)
	{
		tObjectPos.y = this->m_WorldSize.y;
	}
	else if (tObjectPos.y > this->m_WorldSize.y)
	{
		tObjectPos.y = 0.0f;
	}

	Object->SetPosition(tObjectPos);
}
