#include <iostream>
#include <memory>

#include "Game/Asteroid.h"
#include "Game/AsteroidsUI.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain(sf::Vector2u WorldSize)
	:LevelBase(WorldSize)
	, m_MaxPlayerLives(3)
	, m_PlayerLives(-1)
	, m_GameState(EGameState::Menu)
	, m_AsteroidsNumMax(12)
	, m_PlayerScore(0)
{

}

LevelMain::~LevelMain()
{
}

void LevelMain::Initialise()
{
	LevelBase::Initialise();

	switch (this->m_GameState)
	{
	case EGameState::Game:
	{
		// Create and Initialise PlayerSpaceShip
		std::shared_ptr<GameObject> tPlayerShip = std::make_shared<PlayerSpaceShip>();
		this->AddObject(tPlayerShip);
		this->m_PlayerSpaceShip = std::static_pointer_cast<PlayerSpaceShip>(tPlayerShip);

		// If PlayerLives is not default value (-1), this means that the player existed and has been already destroyed
		// if it's -1, initialse a player object and set the current lives number to the max lives value
		if (this->m_PlayerLives == -1)
		{
			this->m_PlayerLives = this->m_MaxPlayerLives;
		}

		tPlayerShip->SetPosition(sf::Vector2f(this->m_WorldSize.x / 2, this->m_WorldSize.y / 2));

		//Create and Initialise Asteroids
		this->SpawnAsteroids();
		break;
	}
	case EGameState::Menu:
	{
		this->m_PlayerScore = 0;
	}
	default:
		break;
	}

	// Initialise AndroidsUI
	this->m_AsteroidsUI.reset();
	this->m_AsteroidsUI = nullptr;
	this->m_AsteroidsUI = std::make_shared<AsteroidsUI>();
	this->m_AsteroidsUI->Initialise(this);
}

void LevelMain::Update(float DeltaTime)
{
	LevelBase::Update(DeltaTime);

	if (this->m_PlayerSpaceShip.expired() || !this->m_PlayerSpaceShip.lock().get()->IsValid())
	{
		if (this->m_PlayerLives == -1)
		{
			return;
		}

		this->m_PlayerLives--;

		if (this->m_PlayerLives <= 0)
		{
			this->m_GameState = EGameState::Endgame;
		}

		this->Reinitialise();

		return;
	}

	this->SpawnAsteroids();


	this->m_AsteroidsUI->Update(*this);
}

void LevelMain::HandleInput(sf::Keyboard::Key Key, bool IsPressed)
{
 	if (this->m_PlayerSpaceShip.lock().get())
	{
		if (this->m_PlayerLives >= 0)
		{
			m_PlayerSpaceShip.lock()->HandleInput(Key, IsPressed);
		}
	}

	switch (this->m_GameState)
	{
	case EGameState::Menu:
	{
		if (Key == sf::Keyboard::Enter && IsPressed)
		{
			this->m_GameState = EGameState::Game;

			this->Reinitialise();
		}

		break;
	}
	case EGameState::Game:
	{
		if (Key == sf::Keyboard::Escape && IsPressed)
		{
			this->m_GameState = EGameState::Endgame;

			this->Reinitialise();
		}

		break;
	}
	case EGameState::Endgame:
	{
		if (Key == sf::Keyboard::Enter && IsPressed)
		{
			this->m_GameState = EGameState::Menu;

			this->Reinitialise();
		}

		break;
	}
	default:
		break;
	}

	for (unsigned int i = this->m_ActiveAsteroids.size(); i-- > 0;)
	{
		if (this->m_ActiveAsteroids[i].expired())
		{
	 		this->m_ActiveAsteroids.erase(this->m_ActiveAsteroids.begin() + i);
		}
	}
}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);

	this->m_AsteroidsUI->Render(RenderWindow);
}

void LevelMain::InitialiseGameUI()
{

}

void LevelMain::SpawnAsteroids()
{
	sf::Vector2f tAsteroidPos(0.0f, 0.0f);
	for (this->m_ActiveAsteroids.size(); this->m_ActiveAsteroids.size() < this->m_AsteroidsNumMax;)
	{
		std::shared_ptr<GameObject> tAsteroid = std::make_shared<Asteroid>(47.0f, 3.0f);
		this->AddObject(tAsteroid);
		tAsteroid->SetPosition(tAsteroidPos);
		tAsteroidPos.x += 200.0f;
		std::weak_ptr<Asteroid> tAsteroidWeakPtr = std::dynamic_pointer_cast<Asteroid>(tAsteroid);
		tAsteroidWeakPtr.lock().get()->SetCanMultiply(true, 2);

		this->m_ActiveAsteroids.push_back(std::weak_ptr<Asteroid>(tAsteroidWeakPtr));
	}
}
