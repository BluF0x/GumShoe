#include "User.h"
#include "Note.h"
#include <SDL3/SDL_mouse.h>

Entity* User::getHover() {
	return hover;
}

Entity* User::getSelection() {
	return selection;
}

void User::renderToolPreview(SDL_Renderer* renderer) {
	switch (currentTool) {
	case SELECTION:
		break;
	case NOTE:
		if (!isDragging) {
			templateNote->moveTo(mousePos, true);
			templateNote->render(renderer);
		}
		break;
	default:
		break;
	}
}

void User::changeTool(Tools tool) {
	SDL_SystemCursor cursorID = SDL_SYSTEM_CURSOR_DEFAULT;

	switch (tool) {
        case SELECTION:
          SDL_ShowCursor();
          currentTool = Tools::SELECTION;
          hover ? cursorID = SDL_SYSTEM_CURSOR_POINTER
                : cursorID = SDL_SYSTEM_CURSOR_DEFAULT;
          break;
        case NOTE:
          SDL_HideCursor();
          currentTool = Tools::NOTE;
          break;
        case RESIZE:
          currentTool = Tools::RESIZE;

          switch (resizeNumber) {
			case 0:
				cursorID = SDL_SYSTEM_CURSOR_NW_RESIZE;
				break;
			case 1:
				cursorID = SDL_SYSTEM_CURSOR_N_RESIZE;
				break;
			case 2:
				cursorID = SDL_SYSTEM_CURSOR_NE_RESIZE;
				break;
			case 3:
				cursorID = SDL_SYSTEM_CURSOR_W_RESIZE;
				break;
			case 4:
				cursorID = SDL_SYSTEM_CURSOR_E_RESIZE;
				break;
			case 5:
				cursorID = SDL_SYSTEM_CURSOR_SW_RESIZE;
				break;
			case 6:
				cursorID = SDL_SYSTEM_CURSOR_S_RESIZE;
				break;
			case 7:
				cursorID = SDL_SYSTEM_CURSOR_SE_RESIZE;
				break;
			default:
				cursorID = SDL_SYSTEM_CURSOR_NWSE_RESIZE;
        }
    }

    cursor = SDL_CreateSystemCursor(cursorID);
	SDL_SetCursor(cursor);
}

void User::setHover(Entity* inHover) {
	if (inHover) {
		if (inHover != hover && hover) {
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

void User::setSelection() {
	if (selection != hover) {
		if (selection) selection->setSelected(false);
		selection = hover;
		if (selection) selection->setSelected(true);
	}
}

void User::setSelection(Entity* entity) {
	if (entity) {
		selection = entity;
		selection->setSelected(true);
		hover = entity;
		hover->setHover(true);
	}
	else {
		selection = nullptr;
		hover = nullptr;
	}
}

void User::setMousePos(float x, float y) {
	mousePos.x = x;
	mousePos.y = y;

	deltaPos = {
		mousePos.x - prevPos.x,
		mousePos.y - prevPos.y
	};

	prevPos.x = x;
	prevPos.y = y;
}

SDL_FPoint User::getMousePos() {
	return mousePos;
}

SDL_FPoint User::getDeltaPos() {
	return deltaPos;
}

User::User(SDL_Color backgroundColor) {
	templateNote = new Note(
		backgroundColor,
		mousePos,
		200.f,
		200.f,
		{ 0.89f, 0.875f, 0.035f, 0.5f }
	);
}

User::~User() {
	delete templateNote;
}
