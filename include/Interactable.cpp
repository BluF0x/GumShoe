#include "Interactable.h"

void Interactable::setSelected(bool selectState) {
	selected = selectState;
	recalculateVertex();
}

void Interactable::setColor(SDL_FColor color) {
	primaryColor = color;
	setSelectionColor(color);
	updateColor();
	recalculateVertex();
}

void Interactable::setHover(bool hoverState) {
	hovered = hoverState;
	updateColor();
	recalculateVertex();
}

void Interactable::updateColor() {
	currentColor = (hovered) ? selectionColor : primaryColor;
}

void Interactable::setSelectionColor(SDL_FColor color) {
	selectionColor = {
		color.r * 0.8f,
		color.g * 0.8f,
		color.b * 0.8f,
		color.a * 1.0f
	};
}
