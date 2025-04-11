#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_stdinc.h>
#include <cstdint>

class Entity
{
public: 
	const int indices[6] = {0, 1, 2, 1, 2, 3}; //Indices for render order 
	bool selected = false;
	bool hovered = false;
	bool isSelectable = true;
	bool isVisible = true;
	float zPos = 1.0f;
	float width = 0;
	float height = 0;
	SDL_FPoint relativeDistance;
	SDL_FPoint position;
	SDL_Vertex vertices[4];
	SDL_FColor currentColor;
	SDL_FColor shadowColor;
	SDL_Vertex shadowVertices[4];

	virtual void render(SDL_Renderer* renderer);

	virtual void setHover(bool hoverState);
	virtual void setSelected(bool selectState);
	virtual void calcVertices();
	virtual void setColor(SDL_FColor color);
	virtual void changeZ(float z);
	
	
	void correctSize();
	void resize(int direction, SDL_FPoint mousePos);
	int8_t  checkResize(SDL_FPoint mousePos);
	void calcShadowVertices();
	void recalculateVertex();
	void setRelativeDistance(SDL_FPoint point);
	void moveTo(SDL_FPoint location, bool isOrigin = false);
	bool checkSelection(SDL_FPoint mousePos);
};
