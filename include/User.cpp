#include "User.h"
#include "Note.h"

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
	switch (tool) {
	case SELECTION:
		SDL_ShowCursor();
		currentTool = Tools::SELECTION;
		break;
	case NOTE:
		SDL_HideCursor();
		currentTool = Tools::NOTE;
		break;
	}
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
