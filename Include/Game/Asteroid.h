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

private:
    float m_AsteroidShapeRadius;
    int m_MeshVertNum;
    sf::Vector2f m_Velocity;
    float m_MaxSpeed;

    float m_LinearAcceleration;
    float m_AngularAcceleration;
};

