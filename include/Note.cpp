#include "Note.h"

Note::Note(SDL_Color backgroundColor, SDL_FPoint pos, float inWidth, float inHeight, SDL_FColor color)
{
	primaryColor = color;
	currentColor = color;
	shadowColor = {
		backgroundColor.r / 100.f * 0.15f,
		backgroundColor.g / 100.f * 0.15f,
		backgroundColor.b / 100.f * 0.15f,
		0.5f
	};

	setSelectionColor(color);
	position = pos;
	width = inWidth;
	height = inHeight;

	recalculateVertex();
}
