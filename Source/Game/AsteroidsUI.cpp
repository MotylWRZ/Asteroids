
#include "Game/AsteroidsUI.h"


AsteroidsUI::AsteroidsUI()
	:m_UIGameTextPosition(sf::Vector2f(51.0f, 10.0f))
	,m_UIShipIconsSpacing(17.0f)
	,m_UIShipIconsPosition(sf::Vector2f(36.0f, 47.0f))
	,m_TextCharSize(34.0f)
{
	this->m_TextFont.loadFromFile("Assets/Fonts/Roboto-Regular.ttf");
}

AsteroidsUI::~AsteroidsUI()
{
}

void AsteroidsUI::Initialise(LevelMain* Level)
{
	if (!Level)
	{
		return;
	}

	this->m_UITextElements.clear();
	this->m_UIShipIcons.clear();

	switch (Level->GetGameState())
	{
	case EGameState::Menu:
	{
		sf::Text tMenuText;
		tMenuText.setFont(this->m_TextFont);
		tMenuText.setCharacterSize(this->m_TextCharSize * 2.0f);
		tMenuText.setString("Asteroids");
		tMenuText.setPosition(Level->GetWorldSize().x / 2, Level->GetWorldSize().y / 2 - 100.0f);
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tMenuText);

		tMenuText.setCharacterSize(this->m_TextCharSize);
		tMenuText.setString("Press ENTER to start the game");
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		tMenuText.setPosition(Level->GetWorldSize().x / 2, Level->GetWorldSize().y / 2);
		this->m_UITextElements.push_back(tMenuText);

		tMenuText.setString("Press ESC to exit the game");
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		tMenuText.setPosition(Level->GetWorldSize().x / 2, Level->GetWorldSize().y / 2 + 100.0f);
		this->m_UITextElements.push_back(tMenuText);

		break;
	}
	case EGameState::Game:
	{
		const PlayerSpaceShip* tSpaceShip = Level->GetPlayerShip();

		if (!tSpaceShip)
		{
			return;
		}

		// Setup  the mesh icons
		std::vector<sf::Vertex> tSpaceShipMesh = tSpaceShip->GetMesh();

		float tOffsetX = 17.0f;
		sf::Vector2f tPosition = this->m_UIShipIconsPosition;

		for (size_t i = 0; i < Level->GetPlayerLives(); i++)
		{
			std::shared_ptr<GameObject> tShipIcon = std::make_shared<GameObject>();
			tShipIcon->SetMesh(tSpaceShipMesh);
			tShipIcon->SetScale(0.3f);
			tShipIcon->SetPosition(tPosition);
			tShipIcon->Initialise(Level);
			this->m_UIShipIcons.push_back(tShipIcon);

			tPosition.x += this->m_UIShipIconsSpacing;
		}

		sf::Text tScoreText;
		tScoreText.setFont(this->m_TextFont);
		tScoreText.setCharacterSize(this->m_TextCharSize);
		tScoreText.setString(std::to_string(Level->GetPlayerScore()));
		tScoreText.setOrigin(tScoreText.getLocalBounds().width / 2, tScoreText.getLocalBounds().height / 2);
		tScoreText.setPosition(tScoreText.getLocalBounds().width / 2, 0.0f);
		tScoreText.setPosition(this->m_UIGameTextPosition);
		this->m_UITextElements.push_back(tScoreText);

		break;
	}
	case EGameState::Endgame:
	{
		sf::Text tMenuText;
		tMenuText.setFont(this->m_TextFont);
		tMenuText.setCharacterSize(this->m_TextCharSize);

		std::string tString = "You destroyed " + std::to_string(Level->GetPlayerScore());

		Level->GetPlayerScore() == 1 ? tString += " Asteroid." : tString += " Asteroids.";

		tMenuText.setString(tString);
		tMenuText.setPosition(Level->GetWorldSize().x / 2, Level->GetWorldSize().y / 2 - 100.0f);
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		this->m_UITextElements.push_back(tMenuText);

		tMenuText.setString("Press ENTER to return to main menu");
		tMenuText.setOrigin(tMenuText.getLocalBounds().width / 2, tMenuText.getLocalBounds().height / 2);
		tMenuText.setPosition(Level->GetWorldSize().x / 2, Level->GetWorldSize().y / 2 + 100.0f);
		this->m_UITextElements.push_back(tMenuText);

		break;
	}
	default:
		break;
	}
}

void AsteroidsUI::Update(const LevelMain& Level)
{
	size_t tStringSizePrevious = this->m_UITextElements[0].getString().getSize();

	this->m_UITextElements[0].setString(std::to_string(Level.GetPlayerScore()));

	size_t tStringSize = this->m_UITextElements[0].getString().getSize();

	// Apply offset
	if (tStringSize > 1 && tStringSize > tStringSizePrevious)
	{
		sf::Vector2f tPosition = this->m_UITextElements[0].getPosition();
		float tOffsetX = this->m_UITextElements[0].getLocalBounds().width / 2 / tStringSize;
		tPosition.x -= tOffsetX;
 		this->m_UITextElements[0].setPosition(tPosition);
	}
}

void AsteroidsUI::Render(sf::RenderWindow& RenderWindow)
{
	for (auto& tText : this->m_UITextElements)
	{
		RenderWindow.draw(tText);
	}

	for (auto& tSpaceShipIcon : this->m_UIShipIcons)
	{
		tSpaceShipIcon->Render(RenderWindow);
	}
}
