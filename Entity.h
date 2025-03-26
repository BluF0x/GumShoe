#pragma once
#include <SDL3/SDL.h>

class Entity
{
public: 
	SDL_FPoint position;
	virtual void render(SDL_Renderer* renderer) {};
	
};

