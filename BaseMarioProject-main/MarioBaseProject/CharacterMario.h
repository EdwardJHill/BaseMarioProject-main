#pragma once
#include "Character.h"
#include <string>
#include <string.h>
class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);

};

