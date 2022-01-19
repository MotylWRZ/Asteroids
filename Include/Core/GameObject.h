#pragma once

#include "SFML/Graphics.hpp"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise();
	virtual void Update(float DeltaTime);
	virtual void Render(sf::RenderWindow& Window);

	inline virtual const sf::Vector2f& GetPosition() const { return this->m_Position; }

	inline virtual void SetPosition(sf::Vector2f NewPosition) { this->m_Position = NewPosition; }
	inline virtual void SetShader(const std::string& Filename, sf::Shader::Type ShaderType);
	inline virtual void SetShader(const std::string& VertShaderFilename, const std::string& FragShaderFilename);
	inline virtual void SetShader(const std::string& VertShaderFilename, const std::string& GeomShaderFilename, const std::string& FragShaderFilename);

	inline const sf::Shader& GetShader() { return *this->m_Shader.get(); }

	inline void ResetShaders() { m_Shader.reset(); };

protected:
	sf::Vector2f m_Position;
	float m_Angle;
	std::vector<sf::Vertex> m_ObjectMesh;

	sf::PrimitiveType m_MeshPrimitiveType;

private:
	std::vector<sf::Vertex> m_TransformedMesh;
	std::unique_ptr<sf::Shader> m_Shader;
};

