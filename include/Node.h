#pragma once
template <typename T>
class Node
{
public:
	T* object;
	Node<T>* next;

	Node(T* obj) : object(obj), next(nullptr) {}
	//~Node() { delet data };
};

