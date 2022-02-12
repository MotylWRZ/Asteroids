#include "SFML/Graphics.hpp"

#include <iostream>

#include "Core/LevelBase.h"

#include "Core/GameObject.h"

GameObject::GameObject()
	:m_Position(sf::Vector2f(100.0f, 100.0f))
	,m_Angle(0.0f)
	,m_MeshPrimitiveType(sf::PrimitiveType::LineStrip)
	,m_IsValid(false)
	,m_Level(nullptr)
	,m_Scale(1.0f)
{
}

GameObject::GameObject(const GameObject& Other)
	:m_Position(Other.GetPosition())
	,m_Angle(Other.GetAngle())
	,m_MeshPrimitiveType(Other.GetPrimitiveType())
	,m_IsValid(Other.IsValid())
	,m_Level(Other.GetLevelPtr())
	,m_Scale(Other.GetScale())
{
}

GameObject::~GameObject()
{
}

void GameObject::Initialise(LevelBase* Level)
{
	if (this->IsValid())
	{
		std::cout << "Object already has been initialised. The object has been reinitialised." << std::endl;
		this->m_ObjectMesh.clear();
		this->m_TransformedMesh.clear();
		return;
	}

	if (!Level)
	{
		std::cout << "Cannot initialise an object with an invalid level pointer." << std::endl;
		return;
	}

	this->ApplyTranform();

	this->m_Level = Level;
	this->m_IsValid = true;
}

void GameObject::Update(float DeltaTime)
{
	if (!this->m_IsValid)
	{
		return;
	}

	this->ApplyTranform();
}

void GameObject::Render(sf::RenderWindow& Window)
{
	if (!this->m_IsValid || this->m_TransformedMesh.size() == 0)
	{
		return;
	}

	if (this->m_Shader)
	{
		Window.draw(&this->m_TransformedMesh[0], this->m_TransformedMesh.size(), this->m_MeshPrimitiveType, this->m_Shader.get());
		return;
	}

	Window.draw(&this->m_TransformedMesh[0], this->m_TransformedMesh.size(), this->m_MeshPrimitiveType);
}

void GameObject::ApplyTranform()
{
	this->m_TransformedMesh = this->m_ObjectMesh;


	//Rotate
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x = this->m_ObjectMesh[i].position.x * cosf(this->m_Angle) - this->m_ObjectMesh[i].position.y * sinf(this->m_Angle);
		this->m_TransformedMesh[i].position.y = this->m_ObjectMesh[i].position.x * sinf(this->m_Angle) + this->m_ObjectMesh[i].position.y * cosf(this->m_Angle);
	}

	// Scale
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x *= this->m_Scale;
		this->m_TransformedMesh[i].position.y *= this->m_Scale;
	}

	// Translate
	for (unsigned int i = 0; i < this->m_TransformedMesh.size(); i++)
	{
		this->m_TransformedMesh[i].position.x += this->m_Position.x;
		this->m_TransformedMesh[i].position.y += this->m_Position.y;
	}
}

inline void GameObject::SetShader(const std::string& Filename, sf::Shader::Type ShaderType)
{
	if (!this->m_Shader)
	{
		this->m_Shader = std::make_unique<sf::Shader>();
	}

	try
	{
		if (!this->m_Shader->loadFromFile(Filename, ShaderType))
		{
			throw 10;
		}
	}

	catch (int x)
	{
		std::cout << "An exception occurred. Exception Number: " << x << " Shader Filename incorrect." << std::endl;
	}
}

inline void GameObject::SetShader(const std::string& VertShaderFilename, const std::string& FragShaderFilename)
{
	if (!this->m_Shader)
	{
		this->m_Shader = std::make_unique<sf::Shader>();
	}

	try
	{
		if (this->m_Shader->loadFromFile(VertShaderFilename, FragShaderFilename))
		{
			throw 10;
		}

	}
	catch (int x)
	{
		std::cout << "An exception occurred. Exception Number: " << x << " Shader Filename incorrect." << std::endl;
	}
}

inline void GameObject::SetShader(const std::string& VertShaderFilename, const std::string& GeomShaderFilename, const std::string& FragShaderFilename)
{
	if (!this->m_Shader)
	{
		this->m_Shader = std::make_unique<sf::Shader>();
	}

	try {
		if (!this->m_Shader->loadFromFile(VertShaderFilename, GeomShaderFilename, FragShaderFilename))
		{
			throw 10;
		}
	}

	catch (int x)
	{
			std::cout << "An exception occurred. Exception Number: " << x << " Shader Filename incorrect." << std::endl;
	}
}
