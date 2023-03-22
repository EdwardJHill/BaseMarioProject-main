#include "CharacterMario.h"
CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture =
}


