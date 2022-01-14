#pragma once

#include "SFML/Graphics.hpp"

#include "Core/LevelBase.h"

class PlayerSpaceShip;

class LevelMain :
    public LevelBase
{
public:
    LevelMain(sf::Vector2u WorldSize);
    virtual ~LevelMain();

    virtual void Initialize() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleInput(sf::Keyboard::Key Key, bool IsPressed) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;

    void WrapObjectCoordinates(GameObject* Object);

private:
    PlayerSpaceShip* m_PlayerSpaceShip;


};

