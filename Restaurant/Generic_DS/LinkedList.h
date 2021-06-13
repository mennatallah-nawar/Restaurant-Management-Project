#pragma once
#include "Node.h"
#include "..\Rest\Cook.h"
#include "..\Rest\Order.h"
#include "time.h"



template <typename T>
class LinkedList
{
private:
	Node<T>* Head;
	int count;
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}


	~LinkedList() 
	{
		DeleteAll();
	}


	void InsertBeg(const T& data)
	{
			Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;
	}	//inserts a new node at list head


	void DeleteAll()
	{
	Node<T>* p=Head;

	if(Head==nullptr)
		return ;
	while(p->getNext())
	{
		if(p->getNext()->getNext()==nullptr)
		{
			Node<T>* q=p->getNext();
			p->setNext(nullptr);
			delete q;
			return;
		}
			Node<T>* q=p->getNext();
			p->setNext(q->getNext());
			delete q;
		p=p->getNext();
	}
	count=0;
	}	//Deletes all nodes in the list


	void DeleteFirst()
	{
		if(Head==nullptr)
			return ;
		Node<T>* p=Head;
		p=Head->getNext();
		delete Head;
		Head=p;
	}


	void InsertEnd(const T& data) 
	{

		Node<T>* R=new Node<T>(data);
		Node<T>* p=Head;
		if(Head==nullptr)
		{
			Head=R;
			count++;
		}
		else
		{
		while(p->getNext() !=nullptr)
		{
			p=p->getNext();
		}
		p->setNext(R);
		R=nullptr;
		count++;
		}
	
	}


	bool Remove(T value) 
	{
		Node<T>* p=Head;
		if(Head==nullptr)
			return false;
		while(p->getNext())
		{
			if(p->getNext()->getItem()==value)
			{
				Node<T>* q=p->getNext();
				p->setNext(q->getNext());
				delete q;
				count--;
				return true;
			}
			p=p->getNext();
		}
		return false;
	}


	int getcount() 
	{
		return count;
	}


	bool isEmpty()const
	{
		if(Head==nullptr)
			return true;
		else
			return false;
	}


	T* LinkedList<T>::toArray(int& c) const
	{
		int count = 0;

		Node<T>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}

		c = count;
		if (count == 0)
		{
			return nullptr;
		}
		else
		{
			T* Arr = new T[count];
			p = Head;
			for (int i = 0; i < count; i++)
			{
				Arr[i] = p->getItem();
				p = p->getNext();
			}
			return Arr;
		}

	}


	void sortedcookes() {
		Node<T>* p = Head;
		Node<T>* ptr;
		T data;
		while (p)
		{
			ptr = p->getNext();
			while (ptr)
			{
				if (p->getItem()->getfinishtimeofCurrOrd() > ptr->getItem()->getfinshtimeofCurOrd())
				{

					data = p->getItem();
					p->setItem(ptr->getItem());
					ptr->setItem(data);

				}
				ptr = ptr->getNext();
			}
			p = p->getNext();
		}
	}


	bool Find(int) {

		if(Head==nullptr)
			return false;
		Node<T>* p=Head;
		while(p)
		{
			if(p->getItem()==key)
				return true;
			p=p->getNext();
		}
		return false;
}


	int getOccurrence(const T &value)
	{
		int c=0;
		Node<T>* p=Head;
		while(p)
		{
			if(p->getItem()==value)
				c+=;
			p=p->getNext();
		}
		return c;
	}

	Node<T>* EraseFirstNode()
	{
		int c = 0;
		Node<T>* p = Head;
		if (Head!=nullptr)
		{
			Head = Head->getNext();
			c--;
			p->setNext(nullptr);
		}
		return p;
	}

};