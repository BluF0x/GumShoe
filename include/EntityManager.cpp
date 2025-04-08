#include "EntityManager.h"

void EntityManager::addEntity(Entity* entity) {
	entityList.push_back(entity);
}

int EntityManager::getEntityIndex(Entity* entity) {
	for (int i = 0; i < entityList.size(); i++) {
		if (entity == entityList[i]) return i;
	}
	return -1;
}

Entity* EntityManager::getEntityAtIndex(int index) {
	if (index >= entityList.size() || index < 0) return nullptr;
	return entityList[index];
}

Entity* EntityManager::getLastEntity() {
	if (entityList.empty()) return nullptr;
	return entityList[entityList.size() - 1];
}

bool EntityManager::forwardEntity(Entity* entity) {
	if (!entity) return false;

	bool entityFound = false;
	for (int i = 0; i < entityList.size(); i++) {
		if (!entityFound) {
			if (entityList[i] == entity) {
				entityFound = true;
			}
		} else {
			entityList[i - 1] = entityList[i];
			if (i == entityList.size() - 1) {
				entityList[i] = entity;
			}
		}
	}
	return entityFound;
}

void EntityManager::renderEntities(SDL_Renderer* renderer) {
	for (Entity* e : entityList) {
		e->render(renderer);
	}
}

Entity* EntityManager::checkMouse(SDL_FPoint mousePos) {
	for (int i = entityList.size() - 1; i >= 0; i--) {
		if (entityList[i]->checkSelection(mousePos)) return entityList[i];
	}
	return nullptr;
}

bool EntityManager::removeEntity(Entity* entity) {
	int index = getEntityIndex(entity);
	if (index == -1) return false;
	entityList.erase(entityList.begin() + index);
}
