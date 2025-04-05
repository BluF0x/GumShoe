#include "Entity.h"

void Entity::render(SDL_Renderer* renderer) {
	// Virtual - typically overridden by derived classes
}

void Entity::setHover(bool hoverState) {
	hovered = hoverState;
}

void Entity::setSelected(bool selectState) {
	selected = selectState;
}

void Entity::calcVertices() {
	// Virtual - typically overridden by derived classes
}

void Entity::setColor(SDL_FColor color) {
	// Virtual - typically overridden by derived classes
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
	calcVertices();
}

bool Entity::checkSelection(SDL_FPoint mousePos) {
	bool xCheck = ((mousePos.x >= vertices[0].position.x) && (mousePos.x <= vertices[3].position.x));
	bool yCheck = ((mousePos.y >= vertices[0].position.y) && (mousePos.y <= vertices[3].position.y));
	return (xCheck && yCheck);
}

