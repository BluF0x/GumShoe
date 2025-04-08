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
	void renderEntities(SDL_Renderer* renderer);
	bool forwardEntity(Entity* entity);
	bool removeEntity(Entity* entity);
	int getEntityIndex(Entity* entity);
	Entity* getEntityAtIndex(int index);
	Entity* getLastEntity();
	Entity* checkMouse(SDL_FPoint mousePos);
};
