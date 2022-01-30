#pragma once

#include "Game/PlayerSpaceShip.h"

#include "SFML/Graphics.hpp"

#include "Core/LevelBase.h"

class PlayerSpaceShip;

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

private:
    std::weak_ptr<PlayerSpaceShip> m_PlayerSpaceShip;

};

