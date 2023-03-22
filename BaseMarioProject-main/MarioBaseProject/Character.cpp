#include "Character.h"
#include "Texture2D.h"
#include <iostream>

void Character::MoveLeft(float deltaTime)
{
    m_position.x -= MOVEMENTSPEED * deltaTime;
    m_facing_direction = FACING_LEFT;
}

void Character::MoveRight(float deltaTime)
{
    m_position.x += MOVEMENTSPEED* deltaTime;
    m_facing_direction = FACING_RIGHT;
}

void Character::Jump(float deltaTime)
{
    if (m_can_jump == true)
    {
        m_can_jump = false;
        m_jump_force = INITIAL_JUMP_FORCE;
        m_jumping = true;
        
    }
    std::cout << m_position.y << std::endl;
    
}

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
    m_facing_direction = FACING_LEFT;
    m_moving_left = false;
    m_moving_right = false;
    m_jumping = false;
    m_can_jump = true;
    m_jump_force = INITIAL_JUMP_FORCE;
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
    //deal with jumping first
    if (m_jumping)
    {
        //adjust position
        m_position.y -= m_jump_force * deltaTime;

        //reduce jump force
        m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

        //is jump force 0?
        if (m_jump_force <= 0.0f)
        {
           
            m_jumping = false;
            
        }
    }
    AddGravity(deltaTime);

    if (m_moving_left)
    {
        MoveLeft(deltaTime);
    }
    else if (m_moving_right)
    {
        MoveRight(deltaTime);
    }
		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
        switch (e.type) {
            /* Look for a keypress */
        case SDL_KEYDOWN:
            /* Check the SDLKey values and move change the coords */
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:

                m_moving_left = true;
              
                break;
            case SDLK_RIGHT:
                m_moving_right = true;

                break;
            case SDLK_UP:
                Jump(deltaTime);
                break;
            case SDLK_DOWN:

                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                m_moving_left = false;

                break;
            case SDLK_RIGHT:
                m_moving_right = false;

                break;
            default:
                break;
            }
        }
    
}

void Character::AddGravity(float deltaTime)
{
    if (m_position.y + 64 <= SCREEN_HEIGHT)
    {
        m_position.y += GRAVITY * deltaTime;
    }
    else
    {
        m_can_jump = true;
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
