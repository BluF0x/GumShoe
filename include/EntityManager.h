#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include "Entity.h"

class EntityManager
{
private:
	std::vector<Entity*> entityList;

public:
	void addEntity(Entity* entity);
	int getEntityIndex(Entity* entity);
	Entity* getEntityAtIndex(int index);
	Entity* getLastEntity();
	bool forwardEntity(Entity* entity);
	void renderEntities(SDL_Renderer* renderer);
	Entity* checkMouse(SDL_FPoint mousePos);
};
