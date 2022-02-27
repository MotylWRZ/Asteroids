
#include "Core/LevelBase.h"
#include "Game/LevelMain.h"

#include "Core/Application.h"

Application::Application(unsigned int WindowWidth, unsigned int WindowHeight)
	:m_WindowWidth(WindowWidth)
	,m_WindowHeight(WindowHeight)
	,m_RenderWindow(nullptr)
	,m_IsRunning(false)
	,m_GameLevel(nullptr)
{
	this->m_RenderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(this->m_WindowWidth, this->m_WindowHeight), "Asteroids");
	this->m_WindowWidth = WindowWidth;
	this->m_WindowHeight = WindowHeight;
}

Application::~Application()
{
}

void Application::Run()
{
	this->Initialise();

	// Set the window view
	sf::FloatRect tVisibleArea(0, 0, this->m_WindowWidth, this->m_WindowHeight);
	this->m_RenderWindow->setView(sf::View(tVisibleArea));

	sf::Clock tClock;
	sf::Event tEvent;

	while (this->m_IsRunning && this->m_RenderWindow->isOpen())
	{
		while (m_RenderWindow->pollEvent(tEvent))
		{
			// "close requested" event: we close the window
			if (tEvent.type == sf::Event::Closed)
				m_RenderWindow->close();

			HandleEvent(tEvent);
		}

		sf::Time tDT = tClock.restart();
		this->Update(tDT.asSeconds());
		this->Render();
	}
}

void Application::Initialise()
{
	this->m_IsRunning = true;
	sf::Vector2u tWorldSize(this->m_WindowWidth, this->m_WindowHeight);
	this->m_GameLevel = std::make_shared<LevelMain>(tWorldSize);
	this->m_GameLevel->Initialise();
}

void Application::Update(float DeltaTime)
{
	if (!this->m_GameLevel || !this->m_GameLevel->IsLevelValid())
	{
		this->m_GameLevel.reset();
		this->m_GameLevel = nullptr;
		this->m_IsRunning = false;
		return;
	}

	this->m_GameLevel->Update(DeltaTime);

}

void Application::HandleEvent(const sf::Event& Event)
{
	if (this->m_GameLevel)
	{
		this->m_GameLevel->HandleEvent(Event);
	}
}

void Application::Render()
{
	this->m_RenderWindow->clear();

	if (this->m_GameLevel)
	{
		this->m_GameLevel->Render(*this->m_RenderWindow);
	}

	this->m_RenderWindow->display();
}
