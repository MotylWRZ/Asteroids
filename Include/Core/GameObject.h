#pragma once

#include "SFML/Graphics.hpp"

class LevelBase;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialise(LevelBase* Level);
	virtual void Update(float DeltaTime);
	virtual void Render(sf::RenderWindow& Window);

	inline virtual const sf::Vector2f& GetPosition() const { return this->m_Position; }

	inline virtual void SetPosition(sf::Vector2f NewPosition) { this->m_Position = NewPosition; }
	inline virtual void SetAngle(float Angle) { this->m_Angle = Angle; }
	inline virtual void SetScale(float Scale) { this->m_Scale = Scale; }
	virtual void ApplyTranform();
	inline virtual void SetShader(const std::string& Filename, sf::Shader::Type ShaderType);
	inline virtual void SetShader(const std::string& VertShaderFilename, const std::string& FragShaderFilename);
	inline virtual void SetShader(const std::string& VertShaderFilename, const std::string& GeomShaderFilename, const std::string& FragShaderFilename);

	inline const sf::Shader& GetShader() { return *this->m_Shader.get(); }
	inline bool IsActive() { return this->m_IsActive; }

	inline void ResetShaders() { m_Shader.reset(); };

protected:
	sf::Vector2f m_Position;
	float m_Angle;
	float m_Scale;
	std::vector<sf::Vertex> m_ObjectMesh;
	sf::PrimitiveType m_MeshPrimitiveType;
	bool m_IsActive;
	LevelBase* m_Level;
	std::unique_ptr<sf::Shader> m_Shader;
private:
	std::vector<sf::Vertex> m_TransformedMesh;

};

