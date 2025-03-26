#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"

class Note : public Entity
{
public:
	const int indices[6] = {0, 1, 2, 1, 2, 3};
	SDL_FColor currentColor;
	SDL_FColor selectionColor;
	SDL_FColor primaryColor;
	SDL_Vertex vertices[4];
	float width;
	float height;

	void render(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
		SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, SDL_arraysize(indices));
	}

	void calcVertices() {
		vertices[0].color = currentColor;
		vertices[0].position.x = position.x;
		vertices[0].position.y = position.y;
		vertices[0].tex_coord.x = NULL ;
		vertices[0].tex_coord.y = NULL ;

		vertices[1].color = currentColor;
		vertices[1].position.x = position.x + width;
		vertices[1].position.y = position.y;
		vertices[1].tex_coord.x = NULL ;
		vertices[1].tex_coord.y = NULL ;

		vertices[2].color = currentColor;
		vertices[2].position.x = position.x;
		vertices[2].position.y = position.y + height;
		vertices[2].tex_coord.x = NULL ;
		vertices[2].tex_coord.y = NULL ;

		vertices[3].color = currentColor;
		vertices[3].position.x = position.x + width;
		vertices[3].position.y = position.y + height;
		vertices[3].tex_coord.x = NULL ;
		vertices[3].tex_coord.y = NULL ;

	}

	Note(SDL_FPoint pos, float inWidth = 100.0, float inHeight = 200.0, SDL_FColor color = {1.0, 1.0, 1.0, 1.0}) {
		primaryColor = color;
		currentColor = color;
		selectionColor = {
		color.r * 0.5f,
		color.g * 0.5f,
		color.b * 0.5f,
		color.a = 1.0f
		};
		position = pos;
		width = inWidth;
		height = inHeight;
		
		calcVertices();
	}
};

