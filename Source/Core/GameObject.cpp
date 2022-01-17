#include "SFML/Graphics.hpp"

#include <iostream>

#include "Core/GameObject.h"

GameObject::GameObject()
	:m_Position(sf::Vector2f(100.0f, 100.0f))
	,m_Angle(0.0f)
	,m_MeshPrimitiveType(sf::PrimitiveType::LineStrip)
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialise()
{
}

void GameObject::Update(float DeltaTime)
{
	this->m_TransformedMesh = this->m_ObjectMesh;

	//Rotate
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x = this->m_ObjectMesh[i].position.x * cosf(this->m_Angle) - this->m_ObjectMesh[i].position.y * sinf(this->m_Angle);
		this->m_TransformedMesh[i].position.y = this->m_ObjectMesh[i].position.x * sinf(this->m_Angle) + this->m_ObjectMesh[i].position.y * cosf(this->m_Angle);
	}

	// Translate
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x += this->m_Position.x;
		this->m_TransformedMesh[i].position.y += this->m_Position.y;
	}
}

void GameObject::Render(sf::RenderWindow& Window)
{
	if (this->m_Shader)
	{
		Window.draw(&this->m_TransformedMesh[0], this->m_TransformedMesh.size(), this->m_MeshPrimitiveType, this->m_Shader.get());
		return;
	}
	Window.draw(&this->m_TransformedMesh[0], this->m_TransformedMesh.size(), this->m_MeshPrimitiveType);
}

inline void GameObject::SetShader(const std::string& Filename, sf::Shader::Type ShaderType)
{
	if (!this->m_Shader)
	{
		this->m_Shader = std::make_unique<sf::Shader>();
	}

	if (!this->m_Shader->loadFromFile(Filename, ShaderType))
	{
		try
		{
			throw 0;
		}
		catch (...)
		{
			std::cout << "An exception occurred." << "Shader Filename incorrect" << '\n';
		}
	}
}

inline void GameObject::SetShader(const std::string& VertShaderFilename, const std::string& FragShaderFilename)
{
	if (!this->m_Shader)
	{
		this->m_Shader = std::make_unique<sf::Shader>();
	}

	this->m_Shader->loadFromFile(VertShaderFilename, FragShaderFilename);
}