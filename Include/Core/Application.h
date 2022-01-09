#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class LevelBase;

class Application
{
public:
	Application(unsigned int WindowWidth, unsigned int WindowHeight);
	~Application();

public:
	void Run();

private:
	void Initialise();
	void Update(float DeltaTime);
	void HandleEvent(const sf::Event& pEvent);
	void Render();

private:
	unsigned int m_WindowWidth;
	unsigned int m_WindowHeight;

	std::shared_ptr<sf::RenderWindow> m_RenderWindow;

	bool m_IsRunning;

	std::shared_ptr<LevelBase> m_GameLevel;
};