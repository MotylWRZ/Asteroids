#include <iostream>
#include <memory>

#include "Game/Asteroid.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain(sf::Vector2u WorldSize)
	:LevelBase(WorldSize)
	, m_GameState(EGameState::Menu)
{
	this->m_TextFont.loadFromFile("Assets/Fonts/SpaceMono-Regular.ttf");
}

LevelMain::~LevelMain()
{
}

void LevelMain::Initialise()
{
	LevelBase::Initialise();

	switch (this->m_GameState)
	{
	case EGameState::Menu:
	{

		break;
	}
	case EGameState::Game:
	{

		// Create and Initialise PlayerSpaceShip
		std::shared_ptr<GameObject> tPlayerShip = std::make_shared<PlayerSpaceShip>();
		this->AddObject(tPlayerShip);
		this->m_PlayerSpaceShip = std::static_pointer_cast<PlayerSpaceShip>(tPlayerShip);
		tPlayerShip->SetPosition(sf::Vector2f(this->m_WorldSize.x / 2, this->m_WorldSize.y / 2));

		//Create and Initialise Asteroids
		sf::Vector2f tAsteroidPos(0.0f, 0.0f);
		for (unsigned i = 0; i < 12; i++)
		{
			std::shared_ptr<GameObject> tAsteroid = std::make_shared<Asteroid>(47.0f, 3.0f);
			this->AddObject(tAsteroid);
			tAsteroid->SetPosition(tAsteroidPos);
			tAsteroidPos.x += 200.0f;
			dynamic_cast<Asteroid*>(tAsteroid.get())->SetCanMultiply(true, 2);
		}

		break;
	}
	case EGameState::Endgame:
	{

		break;
	}
	default:
		break;
	}

}

void LevelMain::Update(float DeltaTime)
{
	if (this->m_PlayerSpaceShip.expired())
	{
		return;
	}

	unsigned int tLives = this->m_PlayerSpaceShip.lock().get()->GetLives();
	LevelBase::Update(DeltaTime);

		if (this->m_PlayerSpaceShip.lock().get()->GetLives() < tLives)
		{
			std::cout << "Player destroyed" << std::endl;
		}

		if (this->m_PlayerSpaceShip.expired() || !this->m_PlayerSpaceShip.lock().get()->IsValid())
		{
			this->Reinitialise();
		}
}

void LevelMain::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
 	if (this->m_PlayerSpaceShip.lock().get())
	{
		m_PlayerSpaceShip.lock()->HandleInput(Key, IsPressed);
	}

	switch (this->m_GameState)
	{
	case EGameState::Menu:
	{
		if (Key == sf::Keyboard::Enter)
		{
			this->m_GameState = EGameState::Game;

			this->Reinitialise();
		}

		break;
	}
	case EGameState::Game:
	{

		break;
	}
	case EGameState::Endgame:
	{
		if (Key == sf::Keyboard::Enter)
		{
			this->m_GameState = EGameState::Menu;

			this->Reinitialise();
		}

		break;
	}
	default:
		break;
	}


}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);
}
