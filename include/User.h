#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"

class User
{
private:
	SDL_FPoint mousePos = { 0, 0 };
	SDL_FPoint prevPos = { 0, 0 };
	SDL_FPoint deltaPos = { 0, 0 };
	Entity* selection = nullptr;
	Entity* hover = nullptr;
public:
	bool isActive = false;

	Entity* getHover() {
		return hover;
	}

	Entity* getSelection() {
		return selection;
	}


	void setHover(Entity* inHover) {
		if (inHover) {
			if (inHover != hover && hover){
				hover->setHover(false);
			}
			hover = inHover;
			hover->setHover(true);
		}
		else if (!inHover && hover) {
			hover->setHover(false);
			hover = nullptr;
		}
	}

	void setSelection() {
		if (selection != hover) {
			if (selection) selection->setSelected(false);
			selection = hover;
			if (selection) selection->setSelected(true);
		}
	}
	
	void setMousePos(float x, float y) {
		mousePos.x = x;
		mousePos.y = y;

		deltaPos = {
			mousePos.x - prevPos.x,
			mousePos.y - prevPos.y
		};

		prevPos.x = x;
		prevPos.y = y;
	}

	SDL_FPoint getMousePos() {
		return mousePos;
	}

	SDL_FPoint getDeltaPos() {
		return deltaPos;
	}
};

