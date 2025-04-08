#include "Entity.h"

void Entity::render(SDL_Renderer* renderer) {
	if (isVisible) {
		SDL_RenderGeometry(renderer, NULL, shadowVertices, 4, indices, SDL_arraysize(indices));
		SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, SDL_arraysize(indices));
	}
}

void Entity::setHover(bool hoverState) {
	hovered = hoverState;
}

void Entity::setSelected(bool selectState) {
	selected = selectState;
}

void Entity::calcVertices() {
	for (int i = 0; i < 4; i++) {
		vertices[i].color = currentColor;
		vertices[i].tex_coord.x = 0;
		vertices[i].tex_coord.y = 0;
	}

	float xScale = width * (zPos - 1.0f);
	float yScale = height * (zPos - 1.0f);

	vertices[0].position.x = position.x - xScale;
	vertices[0].position.y = position.y - yScale;

	vertices[1].position.x = position.x + width + xScale;
	vertices[1].position.y = position.y - yScale;

	vertices[2].position.x = position.x - xScale;
	vertices[2].position.y = position.y + height + yScale;

	vertices[3].position.x = position.x + width + xScale;
	vertices[3].position.y = position.y + height + yScale;
}

void Entity::calcShadowVertices() {
	for (int i = 0; i < 4; i++) {
		shadowVertices[i].position.x = vertices[i].position.x + width * (zPos - 1.0f) + 2.f;
		shadowVertices[i].position.y = vertices[i].position.y + height * (zPos - 1.0f) + 2.f;
		shadowVertices[i].color = shadowColor;
		shadowVertices[i].tex_coord.x = 0;
		shadowVertices[i].tex_coord.y = 0;
	}
}

void Entity::resize(int direction, SDL_FPoint mousePos) {
	setRelativeDistance(mousePos);
	switch (direction) {
	case 0: //top left
		position = mousePos;
		width += abs(relativeDistance.x);
		height += abs(relativeDistance.y);
		break;
	case 1: //top middle
		vertices[0].position.y = mousePos.y;
		vertices[1].position.y = mousePos.y;
		break;
	case 2: //top right
		vertices[1].position = mousePos;
		break;
	case 3: //middle left
		vertices[0].position.x = mousePos.x;
		vertices[2].position.x = mousePos.x;
		break;
	case 4: //middle right
		vertices[1].position.x = mousePos.x;
		vertices[3].position.x = mousePos.x;
		break;
	case 5: //bottom left
		vertices[2].position = mousePos;
		break;
	case 6: //bottom middle
		vertices[2].position.y = mousePos.y;
		vertices[3].position.y = mousePos.y;
		break;
	case 7: //bottom right
		vertices[3].position = mousePos;
		vertices[1].position.x = mousePos.x;
		vertices[2].position.y = mousePos.y;
		break;
	}
	width = vertices[1].position.x - vertices[0].position.x;
	height = vertices[2].position.y - vertices[0].position.y;
	recalculateVertex();
}

// Flips position of the vertices so that width and height are always postitive
void Entity::correctSize() {
	if (width < 0) {
		SDL_Vertex bufferVertex = vertices[1];
		vertices[1] = vertices[0];
		vertices[0] = bufferVertex;
		bufferVertex = vertices[3];
		vertices[3] = vertices[2];
		vertices[2] = bufferVertex;
		width = abs(width);
	}
	if (height < 0) {
		SDL_Vertex bufferVertex = vertices[2];
		vertices[2] = vertices[0];
		vertices[0] = bufferVertex;
		bufferVertex = vertices[3];
		vertices[3] = vertices[1];
		vertices[1] = bufferVertex;
		height = abs(height);
	}

	position = vertices[0].position;
	recalculateVertex();
}

void Entity::recalculateVertex() {
	calcVertices();
	calcShadowVertices();
}

void Entity::changeZ(float z) {
	zPos = z;
}

void Entity::setColor(SDL_FColor color) {
	currentColor = color;
}

void Entity::setRelativeDistance(SDL_FPoint point) {
	relativeDistance = {
		point.x - position.x,
		point.y - position.y,
	};
}

void Entity::moveTo(SDL_FPoint location, bool isOrigin) {
	if (isOrigin) {
		position = { location.x, location.y };
	}
	else {
		position.x = location.x - relativeDistance.x;
		position.y = location.y - relativeDistance.y;
	}
	recalculateVertex();
}

bool Entity::checkSelection(SDL_FPoint mousePos) {
	if (isSelectable) {
		bool xCheck = ((mousePos.x >= vertices[0].position.x) && (mousePos.x <= vertices[3].position.x));
		bool yCheck = ((mousePos.y >= vertices[0].position.y) && (mousePos.y <= vertices[3].position.y));
		return (xCheck && yCheck);
	}
	else {
		return false;
	}
}

