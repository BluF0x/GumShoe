#pragma once
#include <type_traits>
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "Node.h"
#include "Entity.h"

class EntityManager
{
private:
	std::vector<Entity*> entityList;
public:
	void addEntity(Entity* entity) {
		entityList.push_back(entity);
	}

	void renderEntities(SDL_Renderer* renderer) {
		for (Entity* e : entityList) {
			e->render(renderer);
		}
	}

	Entity* checkMouse(SDL_FPoint mousePos) {
		for (int i = entityList.size() -1; i >= 0; i--) {
			if (entityList[i]->checkSelection(mousePos)) return entityList[i];
		}
		return nullptr;
	}


	
};
