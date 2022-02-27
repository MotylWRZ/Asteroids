#include <iostream>
#include <memory>

#include "Game/Asteroid.h"
#include "Game/AsteroidsUI.h"
#include "Game/AsteroidsSpawner.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain(sf::Vector2u WorldSize)
	:LevelBase(WorldSize)
	,m_MaxPlayerLives(3)
	,m_PlayerLives(-1)
	,m_GameState(EGameState::Menu)
	,m_AsteroidsNumMax(10)
	,m_PlayerScore(0)
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

		// Instantiate the AsteroidsSpawner object
		this->m_AsteroidsSpawner = std::make_shared<AsteroidsSpawner>(this);
		this->m_AsteroidsSpawner->Initialise(1, this->m_AsteroidsNumMax, 2.0f, 1000.0f, 170.0f, 47.0f);

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

	this->m_AsteroidsSpawner->Update(DeltaTime);
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

		if (Key == sf::Keyboard::Escape && IsPressed)
		{
			this->DestroyLevel();
		}

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
}

void LevelMain::Render(sf::RenderWindow& RenderWindow)
{
	LevelBase::Render(RenderWindow);

	this->m_AsteroidsUI->Render(RenderWindow);
}