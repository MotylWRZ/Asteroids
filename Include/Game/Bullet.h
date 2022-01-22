#pragma once
#include "../Include/Core/GameObject.h"

class Bullet : public GameObject
{
public:

	Bullet();
	virtual ~Bullet();

	virtual void Initialise(LevelBase* Level) override;
	virtual void Update(float DeltaTime) override;

private:
	unsigned int m_MeshVertNum;
	float m_BulletShapeRadius;
};

