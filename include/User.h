#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"


enum Tools {
	SELECTION,
	NOTE
};

class User
{
private:
	SDL_FPoint mousePos = { 0, 0 };
	SDL_FPoint prevPos = { 0, 0 };
	SDL_FPoint deltaPos = { 0, 0 };
	Entity* selection = nullptr;
	Entity* hover = nullptr;

public:
	Note* templateNote = nullptr;
	bool isActive = false;
	enum Tools currentTool = Tools::SELECTION;

	Entity* getHover() {
		return hover;
	}

	Entity* getSelection() {
		return selection;
	}

	void renderToolPreview(SDL_Renderer* renderer) {
		switch (currentTool) {
		case 0:
			break;
		case 1:
			templateNote->moveTo(mousePos, true);
			templateNote->render(renderer);
		default:
			break;
		}
	}

	void changeTool(Tools tool) {
		switch (tool) {
		case 0:
			SDL_ShowCursor();
			currentTool = Tools::SELECTION;
			break;
		case 1:
			SDL_HideCursor();
			currentTool = Tools::NOTE;
			break;
		}
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

	User(SDL_Color backgroundColor) {
		templateNote = new Note(
			backgroundColor,
			mousePos,
			200.f,
			200.f,
			{ 0.89f, 0.875f, 0.035f, 0.5f}
		);
	}

	~User() {
		delete templateNote;
	}
};

