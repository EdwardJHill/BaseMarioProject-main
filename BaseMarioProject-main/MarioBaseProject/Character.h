#pragma once
#include "Commons.h"
#include <SDL.h>
#include <iostream>
#include <string>
class Texture2D;
class Character
{
private:
	FACING m_facing_direction;
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position); 
	~Character();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
};
