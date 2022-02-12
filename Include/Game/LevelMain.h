#pragma once

#include "Game/PlayerSpaceShip.h"

#include "SFML/Graphics.hpp"

#include "Core/LevelBase.h"

class PlayerSpaceShip;
class Asteroid;
class AsteroidsUI;

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

    void InitialiseGameUI();

    void SpawnAsteroids();

    inline const PlayerSpaceShip* GetPlayerShip() const { return this->m_PlayerSpaceShip.expired() ? nullptr : this->m_PlayerSpaceShip.lock().get(); }

    inline void SetPlayerLives(unsigned int PlayerLives) { this->m_PlayerLives = PlayerLives; }
    inline unsigned int GetPlayerLives() const { return this->m_PlayerLives; }

    inline void SetPlayerScore(unsigned int Score) { this->m_PlayerScore = Score; }
    inline unsigned int GetPlayerScore() const { return this->m_PlayerScore; }

    inline const EGameState& GetGameState() const { return this->m_GameState; }


private:
    std::weak_ptr<PlayerSpaceShip> m_PlayerSpaceShip;
    unsigned int m_MaxPlayerLives;
    int m_PlayerLives;
    EGameState m_GameState;

    std::shared_ptr<AsteroidsUI> m_AsteroidsUI;

    unsigned int m_AsteroidsNumMax;
    std::vector<std::weak_ptr<Asteroid>> m_ActiveAsteroids;
    unsigned int m_PlayerScore;
};

