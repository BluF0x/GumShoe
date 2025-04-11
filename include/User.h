#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_stdinc.h>
#include <cstdint>
#include "Entity.h"
#include "Note.h"

enum Tools {
	SELECTION,
	NOTE,
	RESIZE
};

class User
{
private:
	SDL_FPoint mousePos = { 0, 0 };
	SDL_FPoint prevPos = { 0, 0 };
	SDL_FPoint deltaPos = { 0, 0 };
	SDL_Cursor* cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
	Entity* selection = nullptr;
	Entity* hover = nullptr;

public:
	Note* templateNote = nullptr;
	bool isButtonDown = false;
	bool isDragging = false;
	enum Tools currentTool = Tools::SELECTION;
	int resizeNumber = -1; //-1 means it wont resize

	User(SDL_Color backgroundColor);
	~User();

	Entity* getHover();
	Entity* getSelection();

	void renderToolPreview(SDL_Renderer* renderer);
	void changeTool(Tools tool);
	void setHover(Entity* inHover);
	void setSelection();
	void setSelection(Entity* entity);
	void setMousePos(float x, float y);
	SDL_FPoint getMousePos();
	SDL_FPoint getDeltaPos();
};
