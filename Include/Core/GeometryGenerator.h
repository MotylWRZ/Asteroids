#pragma once

#include "SFML/Graphics.hpp"

class GeometryGenerator
{
public:
	GeometryGenerator();
	~GeometryGenerator();

	static std::vector<sf::Vertex> GenerateLine(const sf::Vector2f& LineStart, const sf::Vector2f& LineEnd);
	static std::vector<sf::Vertex> GenerateCircle(const sf::Vector2f& Center, float Radius, float NumberOfVertices);
};