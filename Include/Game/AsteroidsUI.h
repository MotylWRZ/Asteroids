#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Core/GameObject.h"

#include "Game/LevelMain.h"

class LevelMain;

class AsteroidsUI
{
public:
	AsteroidsUI();
	~AsteroidsUI();

	void Initialise(LevelMain* Level);
	void Update(const LevelMain& Level);
	void Render(sf::RenderWindow& RenderWindow);

	std::vector<sf::Text> m_UITextElements;
	//std::vector<std::vector<sf::Vertex>> m_UIShipIcons;
	//std::vector<GameObject> m_ShipIcons;
	std::vector<std::shared_ptr<GameObject>> m_UIShipIcons;
	sf::Font m_TextFont;

};