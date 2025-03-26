#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"
class User
{
private:
	SDL_FPoint mousePos = { 0, 0 };
public:
	Entity* selection = nullptr;
	
	void setMousePos(float x, float y) {
		mousePos.x = x;
		mousePos.y = y;
	}
	SDL_FPoint getMousePos() {
		return mousePos;
	}

};

