#pragma once
#include <type_traits>
#include <SDL3/SDL.h>
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

	bool renderNode(SDL_Renderer renderer) {
		Node<T>* temp = head;
		while (temp != last || !temp->next) {
			if constexpr ()
			temp->object->render(renderer);

		}

	}

};

class NodeManager<Entity> {
	Node<Entity>* head;
	Node<Entity>* last;

	NodeManager(Entity* obj) {
		Node<Entity>* newNode = new Node<T>(obj);
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

	bool renderNode(SDL_Renderer renderer) {
		Node<T>* temp = head;
		while (temp != last || !temp->next) {
			if constexpr ()
			temp->object->render(renderer);

		}

	}


};
