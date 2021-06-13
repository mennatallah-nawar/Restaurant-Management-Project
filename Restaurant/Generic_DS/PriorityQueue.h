#pragma once
#include "Node.h"

template < typename T>
class PriorityQueue
{
	Node<T>* backPtr;
    Node<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	//PriorityNode<T>* SearchForOrder(T Ord);
	bool enqueue(const T& newEntry, double Per);
	bool dequeue(T& frntEntry);
	bool peekFront( T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	~PriorityQueue();
};

template < typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template < typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template < typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, double p)
{
	Node<T>* newNodePtr = new Node<T>(newEntry, p);
	Node<T>* dummy = frontPtr;
	//newEntry = newNodePtr->getItem();
	p = newNodePtr->GetPriority();
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else if (dummy->GetPriority() < p) {
		newNodePtr->setNext(dummy);
		frontPtr = newNodePtr;

	}
	else
	{
		while ((dummy->getNext()) && (dummy->getNext()->GetPriority() > p)) {
			dummy = dummy->getNext();
		}

		newNodePtr->setNext(dummy->getNext());
		dummy->setNext(newNodePtr);
	}
	return true;
	
} // end enqueue
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/
template < typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template < typename T>
bool PriorityQueue<T>::peekFront(T&  frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}
///////////////////////////////////////////////////////////////////////////////////

template < typename T>
PriorityQueue<T>::~PriorityQueue()
{

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/
template < typename T>
T* PriorityQueue<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}
	
	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

//template < typename T>
//PriorityNode<T>* PriorityQueue<T>::SearchForOrder(T Ord)
//{
//	PriorityNode<T>* Temp = frontPtr;
//	while (Temp)
//	{
//		if (Temp->getItem() == Ord)
//			return Temp;
//		Temp = Temp->getNext();
//	}
//	return Temp;
//}
