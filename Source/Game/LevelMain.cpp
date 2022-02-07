#include <iostream>
#include <memory>

#include "Game/Asteroid.h"

#include "Game/LevelMain.h"

LevelMain::LevelMain(sf::Vector2u WorldSize)
	:LevelBase(WorldSize)
	, m_MaxPlayerLives(3)
	, m_PlayerLives(-1)
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
		this->m_UITextElements.clear();

		sf::Text tMenuText;
		tMenuText.setFont(this->m_TextFont);
		tMenuText.setString("Asteroids");
		tMenuText.setPosition(this->m_WorldSize.x / 2, this->m_WorldSize.y / 2);
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tMenuText);

		break;
	}
	case EGameState::Game:
	{
		this->m_UITextElements.clear();

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
		sf::Text tMenuText;
		tMenuText.setFont(this->m_TextFont);
		tMenuText.setString("Congratulations ! You destroyed: 0 Asteroids.");
		tMenuText.setPosition(this->m_WorldSize.x / 2, this->m_WorldSize.y / 2);
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tMenuText);
		break;
	}
	default:
		break;
	}

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

		std::cout << "Player destroyed" << std::endl;

		if (this->m_PlayerLives <= 0)
		{
			this->m_GameState = EGameState::Endgame;
		}

		this->Reinitialise();

		return;
	}
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

	for (sf::Text& tText : this->m_UITextElements)
	{
		RenderWindow.draw(tText);
	}
}
