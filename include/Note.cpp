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

void Note::prepareResize(Entity resizeEntities[8]) {
	float borderSize = 3.0f;
	float heightBorder = height - borderSize*2;
	float widthBorder = width - borderSize*2;

	float positionBorderX = position.x + width - borderSize;
	float positionBorderY = position.y + height - borderSize;

	resizeEntities[0].position = vertices[0].position;
	resizeEntities[0].width = resizeEntities[0].height = borderSize;

	resizeEntities[1].position = {position.x + borderSize, position.y};
	resizeEntities[1].width = widthBorder;	
	resizeEntities[1].height = height;

	resizeEntities[2].position = {positionBorderX, position.y};
	resizeEntities[2].width = resizeEntities[2].height = borderSize;

	resizeEntities[3].position = {position.x, position.y + borderSize};
	resizeEntities[3].height = heightBorder;
	resizeEntities[3].width = borderSize;

	resizeEntities[4].position = {positionBorderX, position.y + borderSize};
	resizeEntities[4].height = heightBorder;
	resizeEntities[4].width = borderSize;

	resizeEntities[5].position = {position.x, positionBorderY};
	resizeEntities[5].height = resizeEntities[5].width = borderSize;

	resizeEntities[6].position = {position.x + borderSize, positionBorderY};
	resizeEntities[6].width = widthBorder;
	resizeEntities[6].height = borderSize;

	resizeEntities[7].position = {positionBorderX, positionBorderY};
	resizeEntities[7].width = resizeEntities[7].height = borderSize;


	for (int i = 0; i < 8; i++){
		resizeEntities[i].calcVertices();
	}


}

int Note::checkResize(SDL_FPoint mousePos) {
	float halfHeight = height/2;
	float halfWidth = width/2;
	float borderSize = 4.0f;

	SDL_FPoint centerPoint = {
		position.x + halfWidth, 
		position.y + halfHeight 
	};

	bool verticalCheck = (mousePos.x <= position.x + borderSize || mousePos.x >= position.x + width - borderSize );
	bool horizontalCheck = (mousePos.y <= position.y + borderSize || mousePos.y >= position.y + height - borderSize);

	// checks if corner
	if (verticalCheck && horizontalCheck){
		// checks which quadrant is selected
		if ( mousePos.x < halfHeight && mousePos.y < halfHeight){
			return 0;
		}
		else if (mousePos.x > halfHeight && mousePos.y < halfHeight) {
			return 2;
		}
		else if (mousePos.x < halfHeight && mousePos.y > halfHeight) {
			return 5;
		}
		else if (mousePos.x > halfHeight && mousePos.y > halfHeight) {
			return 7;
		}
		
	}else if (horizontalCheck) {
		if (mousePos.y < halfHeight) {
			return 1;
		} else {
			return 6;
		}
	}else if (verticalCheck) {
		if (mousePos.x < halfWidth) {
			return 3;
		} else {
			return 4;
		}
	}

	return -1;
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
