#include "Note.h"
#include <SDL3/SDL_rect.h>

void Note::resize(int resizePosition, SDL_FPoint mousePos) {
	switch (resizePosition) {
	case 0: //top left
		vertices[0].position = mousePos;
		break;
	case 1: //top middle 
		vertices[0].position.y = mousePos.y;
		vertices[1].position.y = mousePos.y;
		break;
	case 2: //top right
		vertices[1].position = mousePos;
		break;
	case 3: //left middle 
		vertices[0].position.x = mousePos.x;
		vertices[2].position.x = mousePos.x;
		break;
	case 4: //right middle 
		vertices[1].position.x = mousePos.x;
		vertices[3].position.x = mousePos.x;
		break;
	case 5: //bottom left
		vertices[3].position = mousePos;
		break;
	case 6: //bottom middle
		vertices[2].position.y = mousePos.y;
		vertices[3].position.y = mousePos.y;
		break;
	case 7:
		vertices[3].position = mousePos;
		break;
	}
	recalculateVertex();
}



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
