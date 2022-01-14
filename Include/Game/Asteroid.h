#pragma once
#include "Core/GameObject.h"

class Asteroid :
    public GameObject
{
public:
    Asteroid();
    virtual ~Asteroid();

    virtual void Initialise() override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;
};

