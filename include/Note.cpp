#include "Note.h"

void Note::setSelectionColor(SDL_FColor color) {
	selectionColor = {
		color.r * 0.8f,
		color.g * 0.8f,
		color.b * 0.8f,
		color.a * 1.0f
	};
}

Uint32 Note::deselectCallback(void* userdata, SDL_TimerID timerID, Uint32 interval) {
	Note* note = static_cast<Note*>(userdata);
	note->setSelected(false);
	return 0;
}

void Note::render(SDL_Renderer* renderer) {
	SDL_RenderGeometry(renderer, NULL, shadowVertices, 4, indices, SDL_arraysize(indices));
	SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, SDL_arraysize(indices));
}

void Note::calcShadowVertices() {
	for (int i = 0; i < 4; i++) {
		shadowVertices[i].position.x = vertices[i].position.x + width * (zPos - 1.0f) + 2.f;
		shadowVertices[i].position.y = vertices[i].position.y + height * (zPos - 1.0f) + 2.f;
		shadowVertices[i].color = shadowColor;
		shadowVertices[i].tex_coord.x = 0;
		shadowVertices[i].tex_coord.y = 0;
	}
}

void Note::calcVertices() {
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

	calcShadowVertices();
}

void Note::changeZ() {
	zPos = selected ? 1.1f : 1.0f;
}

void Note::setColor(SDL_FColor color) {
	primaryColor = color;
	setSelectionColor(color);
	updateColor();
	calcVertices();
}

void Note::updateColor() {
	currentColor = (hovered) ? selectionColor : primaryColor;
}

void Note::setSelected(bool selectState) {
	selected = selectState;
	if (selected && timer) {
		SDL_RemoveTimer(timer);
	}
	changeZ();
	calcVertices();
}

void Note::setHover(bool hoverState) {
	hovered = hoverState;
	updateColor();
	calcVertices();

	if (selected) {
		if (!hovered) {
			timer = SDL_AddTimer(1000, deselectCallback, this);
		} else {
			SDL_RemoveTimer(timer);
		}
	}
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

	calcVertices();
}
