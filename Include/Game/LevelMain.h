#pragma once

#include "Game/PlayerSpaceShip.h"

#include "SFML/Graphics.hpp"

#include "Core/LevelBase.h"

class PlayerSpaceShip;
class Asteroid;

enum class EGameState
{
    Menu,
    Game,
    Endgame
};

class LevelMain :
    public LevelBase
{
public:
    LevelMain(sf::Vector2u WorldSize);
    virtual ~LevelMain();

    virtual void Initialise() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;

    void SpawnAsteroids();

    inline void SetPlayerScore(unsigned int Score) { this->m_PlayerScore = Score; }
    inline unsigned int GetPlayerScore() { return this->m_PlayerScore; }


private:
    std::weak_ptr<PlayerSpaceShip> m_PlayerSpaceShip;
    unsigned int m_MaxPlayerLives;
    int m_PlayerLives;
    EGameState m_GameState;

    std::vector<sf::Text> m_UITextElements;
    std::vector<sf::Vertex> m_UIShipIconMesh;
    sf::Font m_TextFont;

    unsigned int m_AsteroidsNumMax;
    std::vector<std::weak_ptr<Asteroid>> m_ActiveAsteroids;
    unsigned int m_PlayerScore;
};

