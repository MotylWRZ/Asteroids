#pragma once
#include "../Include/Core/GameObject.h"

class Bullet : public GameObject
{
public:

	Bullet();
	virtual ~Bullet();

	virtual void Initialise(LevelBase* Level);
	virtual void Update(float DeltaTime);

private:
	unsigned int m_MeshVertNum;
	float m_BulletShapeRadius;
};

