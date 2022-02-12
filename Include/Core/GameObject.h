#pragma once

#include "SFML/Graphics.hpp"

class LevelBase;

class GameObject
{
public:
	GameObject();
	GameObject(const GameObject& Other);

	virtual ~GameObject();

	virtual void Initialise(LevelBase* Level);
	virtual void Update(float DeltaTime);
	virtual void Render(sf::RenderWindow& Window);

	inline virtual void DestroyObject() { this->m_IsValid = false;}
	inline void ResetShaders() { m_Shader.reset(); };

	inline virtual const sf::Vector2f& GetPosition() const { return this->m_Position; }
	inline float GetAngle() const { return this->m_Angle; }
	inline float GetScale() const { return this->m_Scale; }
	inline sf::PrimitiveType GetPrimitiveType() const { return this->m_MeshPrimitiveType; }
	inline LevelBase* GetLevelPtr() const { return this->m_Level; }
	inline const LevelBase& GetLevel() const { return *this->m_Level; }
	inline const sf::Shader& GetShader() const { return *this->m_Shader.get(); }
	inline bool IsValid() const { return this->m_IsValid; }
	inline const std::vector<sf::Vertex>& GetMesh() const { return this->m_ObjectMesh; }
	inline const std::vector<sf::Vertex>& GetMeshTransformed() const { return this->m_TransformedMesh; }

	inline virtual void SetPosition(sf::Vector2f NewPosition) { this->m_Position = NewPosition; }
	inline virtual void SetAngle(float Angle) { this->m_Angle = Angle; }
	inline virtual void SetScale(float Scale) { this->m_Scale = Scale; }
	virtual void ApplyTranform();
	inline virtual void SetShader(const std::string& Filename, sf::Shader::Type ShaderType);
	inline virtual void SetShader(const std::string& VertShaderFilename, const std::string& FragShaderFilename);
	inline virtual void SetShader(const std::string& VertShaderFilename, const std::string& GeomShaderFilename, const std::string& FragShaderFilename);
	inline void SetMesh(const std::vector<sf::Vertex>& Mesh) { this->m_ObjectMesh = Mesh; }

protected:
	sf::Vector2f m_Position;
	float m_Angle;
	float m_Scale;
	std::vector<sf::Vertex> m_ObjectMesh;
	sf::PrimitiveType m_MeshPrimitiveType;
	bool m_IsValid;
	LevelBase* m_Level;
	std::unique_ptr<sf::Shader> m_Shader;
private:
	std::vector<sf::Vertex> m_TransformedMesh;

};

