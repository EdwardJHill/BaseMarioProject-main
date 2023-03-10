#pragma once
#include "Commons.h"
#include <SDL.h>
#include <iostream>
#include <string>


class Texture2D;
class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position); 
	~Character();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
};

