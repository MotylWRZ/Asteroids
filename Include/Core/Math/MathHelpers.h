#pragma once

#include "SFML/Graphics.hpp"

class MathHelpers
{
public:
	MathHelpers();
	~MathHelpers();

	inline static float Dot(const sf::Vector2f& SourceVectorOne, const sf::Vector2f& SourceVectorTwo) { return SourceVectorOne.x * SourceVectorTwo.x + SourceVectorOne.y * SourceVectorTwo.y; }
	static sf::Vector2f NormalizeVector(const sf::Vector2f& SourceVector);
	inline static float GetVectorLength(const sf::Vector2f& SourceVector) { return std::sqrt(MathHelpers::Dot(SourceVector, SourceVector)); }
};

