#pragma once

#include <iostream>
#include <vector>

class Asteroid;
class Level;

class AsteroidsSpawner
{
public:

	AsteroidsSpawner(LevelBase* Level);
	~AsteroidsSpawner() {};

	void Initialise(unsigned int StartingAsteroidsNum = 4, unsigned int MaxAsteroidsNum = 10, float SpawningCooldown = 2.0f, float AsteroidsLinearAcceleration = 200.0f, float AsteroidsMaxSpeed = 100.0f, float AsteroidsSize = 70.0f);
	void Update(float DeltaTime);
	void SpawnMaxAsteroids();
	void SpawnAsteroids(unsigned int AsteroidsToSpawn);

private:
	unsigned int m_StartingAsteroidsNum;
	unsigned int m_MaxAsteroidsNum;
	float m_SpawningCooldown;
	float m_AsteroidLinearAcceleration;
	float m_AsteroidsMaxSpeed;
	float m_AsteroidsSize;
	std::vector<std::weak_ptr<Asteroid>> m_ActiveAsteroids;
	float m_Timer;
	LevelBase* m_Level;
};

