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

	int getEntityIndex(Entity* entity) {
		for (int i = 0; i < entityList.size(); i++) {
			if (entity = entityList[i]) return i;
		}
	};

	Entity* getEntityAtIndex(int index) {
		if (index > entityList.size() || index < 0) return nullptr;
		return entityList[index];
	}

	Entity* getLastEntity() {
		return entityList[entityList.size() - 1];
	}

	bool forwardEntity(Entity* entity) {
		if (!entity) return 0; //Returns if no selection
		bool entityFound = false;
		for (int i = 0; i < entityList.size(); i++) {
			if (!entityFound) {
				if (entityList[i] == entity) {
					entityFound = true;
				}
			}
			else {
				entityList[i - 1] = entityList[i];
				if (i == entityList.size() - 1) {
					entityList[i] = entity;
				}
			}
		}
		return entityFound;
	}

	void renderEntities(SDL_Renderer* renderer) {
		for (Entity* e : entityList) {
			e->render(renderer);
		}
	}

	// Checking needs to be done backwards so that it checks notes on top first
	Entity* checkMouse(SDL_FPoint mousePos) {
		for (int i = entityList.size() -1; i >= 0; i--) {
			if (entityList[i]->checkSelection(mousePos)) return entityList[i];
		}
		return nullptr;
	}

	

	
};
