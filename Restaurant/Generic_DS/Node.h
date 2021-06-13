#pragma once

template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int priority;
public:
	Node();
	Node(const T& r_Item);	//passing by const ref.
	Node(const T& r_Item, int p);
	Node(const T& r_Item, Node<T>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	int GetPriority();
	T getItem() const;
	Node<T>* getNext() const;
}; // end Node


template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, int p)
{
	item = r_Item;
	next = nullptr;
	priority = p;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
int Node<T>::GetPriority()
{
	return priority;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}