#pragma once
#include "Commons.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include "Constants.h"
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
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime);
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position); 
	~Character();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void AddGravity(float deltaTime);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

};

