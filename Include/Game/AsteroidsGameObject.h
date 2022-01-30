#pragma once
#include "Core/Physics/CircleCollider2D.h"

#include "Core/GameObject.h"

class AsteroidsGameObject : public GameObject, public CircleCollider2D
{
public:

	AsteroidsGameObject();
	virtual ~AsteroidsGameObject();

	virtual void Update(float DeltaTime) override;
	virtual void OnCollision(Collider2D* Collider) override = 0;

	virtual void WrapObjectCoordinates();
};

