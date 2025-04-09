#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include "Entity.h"
#include "Interactable.h"

class Note : public Interactable
{
	private:
		Entity* resizeEntities;	


	public:

		void resize(int resizePosition, SDL_FPoint mousePos);
		void prepareResize(Entity resizeEntities[8]);
		int checkResize(SDL_FPoint mousePos);

		Note(SDL_Color backgroundColor, SDL_FPoint pos, float inWidth = 100.0f, float inHeight = 200.0f, SDL_FColor color = {1.0f, 1.0f, 1.0f, 1.0f});
};
