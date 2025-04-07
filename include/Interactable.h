#pragma once
#include "Entity.h"

class Interactable : public Entity {
public:
	SDL_FColor selectionColor;
	SDL_FColor primaryColor;

	void updateColor();
	void setHover(bool hoverState) override;
	void setColor(SDL_FColor color) override;
	void setSelected(bool selectState) override;
	void setSelectionColor(SDL_FColor color);
};

