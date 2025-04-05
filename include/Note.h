#pragma once

#include <SDL3/SDL.h>
#include "Entity.h"

class Note : public Entity
{
private:
	SDL_TimerID timer;
	void setSelectionColor(SDL_FColor color);
	static Uint32 deselectCallback(void* userdata, SDL_TimerID timerID, Uint32 interval);

public:
	const int indices[6] = {0, 1, 2, 1, 2, 3};
	float zPos = 1.0f;
	float zPosMin = 1.0f;
	SDL_FColor currentColor;
	SDL_FColor selectionColor;
	SDL_FColor primaryColor;
	SDL_FColor shadowColor;
	SDL_Vertex shadowVertices[4];

	void render(SDL_Renderer* renderer) override;
	void calcVertices() override;
	void setColor(SDL_FColor color) override;
	void setSelected(bool selectState) override;
	void setHover(bool hoverState) override;

	void calcShadowVertices();
	void updateColor();
	void changeZ();

	Note(SDL_Color backgroundColor, SDL_FPoint pos, float inWidth = 100.0f, float inHeight = 200.0f, SDL_FColor color = {1.0f, 1.0f, 1.0f, 1.0f});
};
