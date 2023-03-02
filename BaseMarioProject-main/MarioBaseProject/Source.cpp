//Be grateful for humble beginnings, because the next level will always require so much more of you
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
using namespace std;
//Globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;
//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();
//Main
int main(int argc, char* args[])
{
	//flag to check if we wish to quit
	
	if (InitSDL())
	{
		bool quit = false;
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();
	return 0;
}
//Setup SDL
bool InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image didn't work . my bad " << IMG_GetError();
				return false;
			}
			g_texture = LoadTextureFromFile("Images/test.bmp");
			if (g_texture == nullptr)
			{
				return false;
			}
			
		}
		else
		{
			cout << "Renderer could not initalise. Error." << SDL_GetError();
			return false;
		}
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

	}

}
void CloseSDL()
{
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//quit sdl subsystems
	IMG_Quit();
	SDL_Quit();
	FreeTexture();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
}
bool Update()
{
	//Event handler
	SDL_Event e;
	//get events
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	}
	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	//Set where to render the texture
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//Render to Screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	//update the screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	//remove the memory used for a previous texture
	FreeTexture();
	SDL_Texture* p_texture = nullptr;
	//load da image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	//create the texture from the pixels on the surface
	p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
	if (p_surface != nullptr)
	{
		cout << "we got nothin "<< SDL_GetError();
	}
	else
	{
		cout << "unable to create texture from surface. Error: " << IMG_GetError();
	}
	SDL_FreeSurface(p_surface);
	return p_texture;
}

void FreeTexture()
{
	//check if texture exists so you can destroy it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}
