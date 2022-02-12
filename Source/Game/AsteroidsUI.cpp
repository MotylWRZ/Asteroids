
#include "Game/AsteroidsUI.h"


AsteroidsUI::AsteroidsUI()
{
	this->m_TextFont.loadFromFile("Assets/Fonts/SpaceMono-Regular.ttf");
}

AsteroidsUI::~AsteroidsUI()
{
}

void AsteroidsUI::Initialise(const LevelMain& Level)
{

	this->m_UITextElements.clear();

	switch (Level.GetGameState())
	{
	case EGameState::Menu:
	{
		sf::Text tMenuText;
		tMenuText.setFont(this->m_TextFont);
		tMenuText.setString("Asteroids");
		tMenuText.setPosition(Level.GetWorldSize().x / 2, Level.GetWorldSize().y / 2);
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tMenuText);

		tMenuText.setString("Press ENTER to start the game");
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		tMenuText.setPosition(Level.GetWorldSize().x / 2, Level.GetWorldSize().y / 2 + 100.0f);
		this->m_UITextElements.push_back(tMenuText);


		break;
	}
	case EGameState::Game:
	{
		const PlayerSpaceShip* SpaceShip = Level.GetPlayerShip();

		if (!SpaceShip)
		{
			return;
		}

		this->m_UIShipIconMesh = SpaceShip->GetMesh();

		sf::Text tScoreText;
		tScoreText.setFont(this->m_TextFont);
		tScoreText.setString("Score");
		tScoreText.setOrigin(tScoreText.getLocalBounds().width / 2, tScoreText.getLocalBounds().height / 2);
		tScoreText.setPosition(Level.GetWorldSize().x - tScoreText.getLocalBounds().width / 2, tScoreText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tScoreText);

		break;
	}
	case EGameState::Endgame:
	{
		sf::Text tMenuText;
		tMenuText.setFont(this->m_TextFont);

		std::string tString = "Congratulations ! You destroyed " + std::to_string(Level.GetPlayerScore());

		Level.GetPlayerScore() == 1 ? tString += " Asteroid." : tString += " Asteroids.";

		tMenuText.setString(tString);
		tMenuText.setPosition(Level.GetWorldSize().x / 2, Level.GetWorldSize().y / 2);
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tMenuText);

		tMenuText.setString("Press ENTER to return to main menu");
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		tMenuText.setPosition(Level.GetWorldSize().x / 2, Level.GetWorldSize().y / 2 + 100.0f);
		this->m_UITextElements.push_back(tMenuText);

		break;
	}
	default:
		break;
	}
}

void AsteroidsUI::Update(const LevelMain& Level)
{
}

void AsteroidsUI::Render(sf::RenderWindow& RenderWindow)
{
	for (auto& tText : this->m_UITextElements)
	{
		RenderWindow.draw(tText);
	}
}
