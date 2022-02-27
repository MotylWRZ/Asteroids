#pragma once

#include "Core/Physics/CircleCollider2D.h"

#include "Game/AsteroidsGameObject.h"

class Asteroid : public AsteroidsGameObject
{
public:
    Asteroid(float Size = 70.0f, float DeformationScale = 10.0f, int verticesNum = 20);
    virtual ~Asteroid();

    virtual void Initialise(LevelBase* Level) override;
    virtual void Update(float DeltaTime) override;
    virtual void Render(sf::RenderWindow& RenderWindow) override;
    virtual void DestroyWithExplosion(float Duration, float Rate);

    virtual void OnCollision(Collider2D* Collider) override;
    inline void SetLinearAcceleration(float LinearAcceleration) { this->m_LinearAcceleration = LinearAcceleration; }
    inline void SetAngularAcceleration(float AngularAcceleration) { this->m_AngularAcceleration = AngularAcceleration; }
    inline void SetMaxSpeed(float MaxSpeed) { this->m_MaxSpeed = MaxSpeed; }
    inline void SetScoreValue(unsigned int ScoreValue) { this->m_ScoreValue = ScoreValue; }
    inline void SetSize(float Radius, float DeformationScale = 10.0f, int VerticesNum = 20);
    void SetCanMultiply(bool CanMultiply, unsigned int ChunksNum = 2);

    inline const float GetLinearAcceleration() const { return this->m_LinearAcceleration; }
    inline const float GetAngularAcceleration() const { return this->m_AngularAcceleration; }
    inline const float GetMaxSpeed() const { return this->m_MaxSpeed; }
    inline const float GetScoreValue() const { return this->m_ScoreValue; }

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
    float m_MovementAngle;
    int m_AngularMovementDirection;
    unsigned int m_ScoreValue;
};

