#include "Core/Application.h"

Application::Application(unsigned int WindowWidth, unsigned int WindowHeight)
{
	this->m_RenderWindow = std::make_shared<sf::RenderWindow>();
	this->m_RenderWindow->setSize(sf::Vector2u(WindowWidth, WindowHeight));
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
}

void Application::Update(float DeltaTime)
{
}

void Application::HandleEvent(const sf::Event& pEvent)
{
}

void Application::Render()
{
}
