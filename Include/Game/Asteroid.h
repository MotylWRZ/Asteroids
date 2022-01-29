#pragma once

#include "Core/Physics/CircleCollider2D.h"

#include "Core/GameObject.h"

class Asteroid : public GameObject, public CircleCollider2D
{
public:
    Asteroid(float Size = 100.0f, float DeformationScale = 10.0f, int verticesNum = 20);
    virtual ~Asteroid();

    virtual void Initialise(LevelBase* Level) override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;

    virtual void OnCollision(Collider2D* Collider) override;
    void SetSize(float Radius, float DeformationScale = 10.0f, int VerticesNum = 20);
    void SetCanMultiply(bool CanMultiply, unsigned int ChunksNum = 2);

private:
    float m_AsteroidShapeRadius;
    int m_MeshVertNum;
    sf::Vector2f m_Velocity;
    float m_MaxSpeed;
    float m_DeformationScale;
    bool m_CanMultiply;
    unsigned int m_ChunksNum;

    float m_LinearAcceleration;
    float m_AngularAcceleration;
};

