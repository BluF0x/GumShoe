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

	virtual void render(SDL_Renderer* renderer) {};

	virtual void setHover(bool hoverState) {
		hovered = hoverState;
	}

	virtual void setSelected(bool selectState) {
		selected = selectState;
	}

	virtual void calcVertices() {};
	
	void setRelativeDistance(SDL_FPoint point) {
		relativeDistance = {
			relativeDistance.x = point.x - position.x,
			relativeDistance.y = point.y - position.y,
		};
	}

	void moveTo(SDL_FPoint location,  bool isOrigin = false) {
		if (isOrigin) {
			position = { location.x , location.y };
		}
		else {
			position.x = location.x - relativeDistance.x;
			position.y = location.y - relativeDistance.y;
		}
		calcVertices();
	}

	bool checkSelection(SDL_FPoint mousePos) {
		bool xCheck = ((mousePos.x >= vertices[0].position.x) && (mousePos.x <= vertices[3].position.x ));
		bool yCheck = ((mousePos.y >= vertices[0].position.y) && (mousePos.y <= vertices[3].position.y ));
		return (xCheck && yCheck);
	}
};

