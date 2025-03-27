#pragma once
#include <SDL3/SDL.h>

class Entity
{
public: 
	float width;
	float height;
	SDL_FPoint position;
	SDL_Vertex vertices[4];
	virtual void render(SDL_Renderer* renderer) {};
	bool checkSelection(SDL_FPoint mousePos) {
		bool xCheck = ((mousePos.x >= position.x) && (mousePos.x <= position.x + width));
		bool yCheck = ((mousePos.y >= position.y) && (mousePos.y <= position.y + height));
		return (xCheck && yCheck);
	}
};

