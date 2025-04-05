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
	SDL_FPoint relativeDistance;
	SDL_FPoint position;
	SDL_Vertex vertices[4];

	virtual void render(SDL_Renderer* renderer);

	virtual void setHover(bool hoverState);
	virtual void setSelected(bool selectState);
	virtual void calcVertices();
	virtual void setColor(SDL_FColor color);

	void setRelativeDistance(SDL_FPoint point);
	void moveTo(SDL_FPoint location, bool isOrigin = false);
	bool checkSelection(SDL_FPoint mousePos);
};
