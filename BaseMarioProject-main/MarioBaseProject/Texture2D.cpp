#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>
using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Texture2D::~Texture2D()
{
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	//remove the memory used for a previous textur
	Free();
	//load da image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	//create the texture from the pixels on the surface
	
	if (p_surface != nullptr)
	{
		//Colour key the image to be transparent
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));
		cout << "we got nothin " << SDL_GetError();
	}
	m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
	if (m_texture == nullptr)
	{
		cout << "Unable to create texture from surface. Error: " << SDL_GetError();
	}
	else
	{
		m_width = p_surface->w;
		m_height = p_surface->h;
	}
	SDL_FreeSurface(p_surface);
	return m_texture != nullptr;
	
}

void Texture2D::Free()
{
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	//gives the texture a place to render
	SDL_Rect renderLocation = { 0,0,m_width,m_height };

	//render to da screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, SDL_FLIP_NONE);
}