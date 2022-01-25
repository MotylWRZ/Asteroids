#include "Core/Math/MathHelpers.h"

#include <vector>

#include"Core/GeometryGenerator.h"

std::vector<sf::Vertex> GeometryGenerator::GenerateLine(const sf::Vector2f& LineStart, const sf::Vector2f& LineEnd)
{
	std::vector<sf::Vertex> tLine{ LineStart, LineEnd };

	return tLine;
}

std::vector<sf::Vertex> GeometryGenerator::GenerateCircle(const sf::Vector2f& Center, float Radius, float NumberOfVertices)
{
	std::vector<sf::Vertex> tCircle;

	// Generate a list of vertices placed around the object position
	for (unsigned int i = 0; i < NumberOfVertices; i++)
	{
		float tAngle = (static_cast<float>(i) / static_cast<float>(NumberOfVertices)) * PI * 2;
		sf::Vector2f  tVertexPos(Radius * sinf(tAngle), Radius * cosf(tAngle));
		tVertexPos += Center;

		tCircle.push_back(sf::Vertex(tVertexPos));
	}

	// Add the last vertex at the position of the first vertex added in order to connect the next to last vertex with the last one
	tCircle.push_back(sf::Vertex(tCircle[0]));

	return tCircle;
}
