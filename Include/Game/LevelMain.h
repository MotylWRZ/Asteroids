#pragma once

#include "SFML/Graphics.hpp"

#include "Core/LevelBase.h"

class PlayerSpaceShip;

class LevelMain :
    public LevelBase
{
public:
    LevelMain();
    virtual ~LevelMain();

    virtual void Initialize() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;

private:
    PlayerSpaceShip* m_PlayerSpaceShip;
};

