#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "Game/LevelMain.h"

class LevelMain;

class AsteroidsUI
{
public:
	AsteroidsUI();
	~AsteroidsUI();

	void Initialise(const LevelMain& Level);
	void Update(const LevelMain& Level);
	void Render(sf::RenderWindow& RenderWindow);

	std::vector<sf::Text> m_UITextElements;
	std::vector<sf::Vertex> m_UIShipIconMesh;
	sf::Font m_TextFont;

};