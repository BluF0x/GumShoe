#pragma once
#include <type_traits>
#include <SDL3/SDL.h>
#include <iostream>
#include "Node.h"
#include "Entity.h"

template <typename T>
class NodeManager
{
public:
	Node<T>* head;
	Node<T>* last;

	NodeManager(T* obj) {
		Node<T>* newNode = new Node<T>(obj);
		head = newNode;
		last = newNode;
	}

	void addNode(T* obj) {
		Node<T>* newNode = new Node<T>(obj);
		Node<T>* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
		last = newNode;
	}
};

template <>
class NodeManager<Entity> 
{
public:
	Node<Entity>* head;
	Node<Entity>* last;

	NodeManager(Entity* obj) {
		Node<Entity>* newNode = new Node<Entity>(obj);
		head = newNode;
		last = newNode;
	}

	void addNode(Entity* obj) {
		Node<Entity>* newNode = new Node<Entity>(obj);
		Node<Entity>* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newNode;
		last = newNode;
	}

	void renderAllNodes(SDL_Renderer* renderer) {
		Node<Entity>* temp = head;
		while (temp) {
			temp->object->render(renderer);
			temp = temp->next;
		}
	}

	Entity* checkSelectedNodes(SDL_FPoint mousePos) {
		Node<Entity>* temp = head;
		while (temp) {
			if (temp->object->checkSelection(mousePos)) return temp->object;
			temp = temp->next;
		}
		return nullptr;
	}


};
