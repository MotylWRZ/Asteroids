#pragma once

#include "Core/Physics/CircleCollider2D.h"

#include "Core/GameObject.h"

class Asteroid : public GameObject, public CircleCollider2D
{
public:
    Asteroid();
    virtual ~Asteroid();

    virtual void Initialise(LevelBase* Level) override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;

    virtual void OnCollision(Collider2D* Collider) override;

private:
    float m_AsteroidShapeRadius;
    int m_MeshVertNum;
    sf::Vector2f m_Velocity;
    float m_MaxSpeed;

    float m_LinearAcceleration;
    float m_AngularAcceleration;
};

