#pragma once

#include "SFML/Graphics.hpp"

#include "Core/LevelBase.h"
class LevelMain :
    public LevelBase
{
public:
    LevelMain();
    virtual ~LevelMain();

    virtual void Initialize() override;
    virtual void Update(float DeltaTime) override;
    virtual void HandleEvent(sf::Event Event) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;
};

