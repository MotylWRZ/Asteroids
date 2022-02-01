#include <random>

#include "Core/Math/MathHelpers.h"

MathHelpers::MathHelpers()
{
}

MathHelpers::~MathHelpers()
{
}

sf::Vector2f MathHelpers::NormalizeVector(const sf::Vector2f& SourceVector)
{
	float tLength = MathHelpers::GetVectorLength(SourceVector);

	if (tLength != 0.0f)
	{
		return sf::Vector2f(SourceVector.x / tLength, SourceVector.y / tLength);
	}
	else
	{
		return SourceVector;
	}
}

void MathHelpers::SetVectorLength(sf::Vector2f* Vector, float NewLength)
{
	float tVectorLength = MathHelpers::GetVectorLength(*Vector);

	if (tVectorLength == 0.0f)
	{
		Vector->x = Vector->x * NewLength;
		Vector->y = Vector->y * NewLength;
		return;
	}

	Vector->x = Vector->x * NewLength / tVectorLength;
	Vector->y = Vector->y * NewLength / tVectorLength;
}

float MathHelpers::GenerateRandomFloatInRange(float Min, float Max)
{
	static std::random_device tRandomDevice;
	std::default_random_engine tRandEngine(tRandomDevice());
	std::uniform_real_distribution<> tRandomDistr(Min, Max);
	tRandomDistr.reset();

	return tRandomDistr(tRandEngine);
}

int MathHelpers::GenerateRandomIntegerInRange(int Min, int Max)
{
	static std::random_device tRandomDevice;
	std::default_random_engine tRandEngine(tRandomDevice());
	std::uniform_int_distribution<> tRandomDistr(Min, Max);
	tRandomDistr.reset();

	return tRandomDistr(tRandEngine);
}
