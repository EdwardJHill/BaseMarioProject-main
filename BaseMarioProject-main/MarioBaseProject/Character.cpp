#include "Character.h"
#include "Texture2D.h"
#include <iostream>

void Character::MoveLeft(float deltaTime)
{
    m_position.x -= 1;
    m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
    m_position.x += 1;
    m_facing_direction = FACING_RIGHT;
}

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
    m_facing_direction = FACING_LEFT;
    m_moving_left = false;
    m_moving_right = true;
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
	//delete m_texture;
	//m_texture = nullptr;
}

void Character::Render()
{
    if (m_facing_direction == FACING_RIGHT)
    {
        m_texture->Render(m_position, SDL_FLIP_NONE);
    }
    else
    {
        m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
    }
}

void Character::Update(float deltaTime, SDL_Event e)
{
    if (m_moving_left)
    {
        MoveLeft(deltaTime);
    }
    else if (m_moving_right)
    {
        MoveRight(deltaTime);
    }
	while (SDL_PollEvent(&e)) {
        
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        switch (e.type) {
            /* Look for a keypress */
        case SDL_KEYDOWN:
            /* Check the SDLKey values and move change the coords */
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                std::cout << "yello left" << m_position.x <<std::endl;
                //m_position.x -= 3;
                m_moving_left = true;
                m_facing_direction = FACING_LEFT;
                break;
            case SDLK_RIGHT:
                std::cout << "yello right"<< m_position.x << std::endl;
                //m_position.x += 3;
                m_moving_right = true;
                m_facing_direction = FACING_RIGHT;
                break;
            case SDLK_UP:
                std::cout << "yello up" << std::endl;
                break;
            case SDLK_DOWN:
                std::cout << "yello down" << std::endl;
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                std::cout << "yello left" << m_position.x << std::endl;
                //m_position.x -= 3;
                m_moving_left = false;

                break;
            case SDLK_RIGHT:
                std::cout << "yello right" << m_position.x << std::endl;
                //m_position.x += 3;
                m_moving_right = false;

                break;
            }
        }
    }
}


void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}
