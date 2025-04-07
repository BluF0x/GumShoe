#pragma once

#include <SDL3/SDL.h>
#include "Interactable.h"

class Note : public Interactable
{
private:

public:


	Note(SDL_Color backgroundColor, SDL_FPoint pos, float inWidth = 100.0f, float inHeight = 200.0f, SDL_FColor color = {1.0f, 1.0f, 1.0f, 1.0f});
};
