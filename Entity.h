#pragma once
#include <SDL3/SDL.h>
#include <iostream>

class Entity
{
public: 
	bool selected = false;
	bool hovered = false;
	float width;
	float height;
	SDL_FPoint position;

	virtual void render(SDL_Renderer* renderer) {};

	virtual void setHover(bool hoverState) {
		hovered = hoverState;
	}

	virtual void setSelected(bool selectState) {
		selected = selectState;
	}

	bool checkSelection(SDL_FPoint mousePos) {
		bool xCheck = ((mousePos.x >= position.x) && (mousePos.x <= position.x + width));
		bool yCheck = ((mousePos.y >= position.y) && (mousePos.y <= position.y + height));
		return (xCheck && yCheck);
	}
};

