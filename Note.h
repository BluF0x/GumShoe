#pragma once
#include <SDL3/SDL.h>
#include "Entity.h"

class Note : public Entity
{
public:
	const int indices[6] = {0, 1, 2, 1, 2, 3};
	float zPos = 1.0f;
	float zPosMin = 1.0f;
	SDL_FColor currentColor;
	SDL_FColor selectionColor;
	SDL_FColor primaryColor;
	SDL_FColor shadowColor;
	SDL_Vertex vertices[4];
	SDL_Vertex shadowVertices[4];
	

	void render(SDL_Renderer* renderer) {
		
	//	SDL_SetRenderDrawColor(renderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
		SDL_RenderGeometry(renderer, NULL, shadowVertices, 4, indices, SDL_arraysize(indices));
		SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, SDL_arraysize(indices));
	}

	void calcShadowVertices() {
		for (int i = 0; i < 4; i++) {
			shadowVertices[i].position.x = vertices[i].position.x + width * (zPos - 1.0f) +1.f;
			shadowVertices[i].position.y = vertices[i].position.y + height * (zPos - 1.0f) +1.f;
			shadowVertices[i].color =  shadowColor ;
			shadowVertices[i].tex_coord.x = NULL ;
			shadowVertices[i].tex_coord.y = NULL ;
		}
	}

	void calcVertices() {
		for (int i = 0; i < 4; i++) {
			vertices[i].color = currentColor;
			vertices[i].tex_coord.x = NULL ;
			vertices[i].tex_coord.y = NULL ;
		}

		float xScale = width * (zPos - 1.0f);
		float yScale = height * (zPos - 1.0f);

		vertices[0].position.x = position.x - xScale ;
		vertices[0].position.y = position.y - yScale;

		vertices[1].position.x = position.x + width +xScale ;
		vertices[1].position.y = position.y - yScale;

		vertices[2].position.x = position.x - xScale;
		vertices[2].position.y = position.y + height + yScale ;

		vertices[3].position.x = position.x + width + xScale;
		vertices[3].position.y = position.y + height + yScale;
		calcShadowVertices();
	}

	void changeZ() {
		if (selected) {
			zPos = 1.1f;
		}
		else {
			zPos = 1.0f;
		}
	}

	void updateColor() {
		currentColor = (hovered) ? selectionColor : primaryColor;
	}

	void setSelected(bool selectState) {
		selected = selectState;
		changeZ();
		calcVertices();
	}

	void setHover(bool hoverState) {
		hovered = hoverState;
		updateColor();
		calcVertices();
	}

	Note(SDL_Color backgroundColor, SDL_FPoint pos, float inWidth = 100.0, float inHeight = 200.0, SDL_FColor color = {1.0, 1.0, 1.0, 1.0} ) {
		primaryColor = color;
		currentColor = color;
		shadowColor = {
		backgroundColor.r /100.f * 0.2f,
		backgroundColor.g /100.f  * 0.2f,
		backgroundColor.b /100.f  * 0.2f,
		backgroundColor.a /100.f  * 0.8f,
		};
		selectionColor = {
		color.r * 0.8f,
		color.g * 0.8f,
		color.b * 0.8f,
		color.a * 1.0f
		};
		position = pos;
		width = inWidth;
		height = inHeight;
	    	
		calcVertices();
	}
};

