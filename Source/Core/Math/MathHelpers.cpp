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