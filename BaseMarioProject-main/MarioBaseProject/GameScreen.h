#pragma once
#include <SDL.h>
#ifndef _GAMESCREEN
#define _GAMESCREEN
class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};
#endif // _GAMESCREEN

