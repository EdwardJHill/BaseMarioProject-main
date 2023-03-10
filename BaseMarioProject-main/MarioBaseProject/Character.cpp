#include "Character.h"
#include "Texture2D.h"
#include <iostream>
Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
}

void Character::Update(float deltaTime, SDL_Event e)
{
	SDL_Event event;
	switch (event.type)
	{
	case SDLK_d:
		std::cout << "it works D" << std::endl;
		m_position.x += 1;
	case SDLK_a:
		std::cout << "it works A" << std::endl;
		m_position.x -= 1;
	default:;

	}
}

void Character::SetPosition(Vector2D new_position)
{
}

Vector2D Character::GetPosition()
{
	return Vector2D();
}
