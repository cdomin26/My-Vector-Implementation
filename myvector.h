//
// myvector class --- a replacement for std::vector based on linked
// nodes of varying-sized array "chunks".  The idea is to avoid the
// reallocation of the underlying dynamic array (and the copying of 
// elements) when the vector becomes full.
//
// Christian Dominguez
// U. of Illinois, Chicago
// CS 341, Spring 2018
// Project #03
//

#pragma once
#include <iostream>
#include <stdlib.h>

using namespace std;

// myvector class file
// myvector<T>

template<typename T>
class myvector
{
private:
	//
	// One node of the vector, i.e. an array "chunk" of size nodeSize.
	//
	class Node
	{
	public:
		T * Elements;
		int NumElems;
		int NodeSize;
		class Node *Next;

		// constructor:
		Node(int nodesize)
			: Elements(new T[nodesize]), NumElems(0), NodeSize(nodesize), Next(nullptr)
		{
		//	string s = "Node: constructor called (size" + to_string(NodeSize) + ")";
		//	Logger::WriteMessage( s.c_str() ); // debug output:

		}

		// destructor:
		~Node()
		{
			// TODO: save this for the last step
		}

		void push_back(const T&e) {
			// NOTE: this function assumes there is room in the node to push
			// another element --- check first before calling!

			Elements[NumElems] = e;
			NumElems++;
		}
	};//End of node class

private:
	
	// Iterator class
	class iterator
	{
	public:
    Node * current;
    int index;

    //Constructor
		iterator(Node *cur, int i)
			: current(c), index(i)
		{}

    //Accessing the next element
		iterator &operator++()
		{
      //When the the number of nodes has reached its capacity and will need to use the array in the next node
      if (current->NodeSize == (index + 1)) {
        index = -1;
        current = current->Next;
      }
      index++;
      return *this;
		}

    //Dereference operator
		T& operator*()
		{
      return current->Elements[index];
		}

    //Comparing two elements
		bool operator!=(const iterator &rhs)
		{
      if ((index == rhs.index) && (current == rhs.current)) {
        return false;
      }
      else {
        return true;
      }

		}

	};//End of iterator class
	
private:
	Node *Head;
	Node *Tail;
	int NumElems;
	int NumNodes;

public:
	myvector()
		: Head(new Node(4)), Tail(Head), NumElems(0), NumNodes(1)
	{
		//Logger::WriteMessage("myvector: constructor called"); //debug output:
	}

  //copy constructor
	myvector(const myvector& other)
    : Head(new Node(4)), Tail(Head), NumElems(0), NumNodes(1)
	{
    int nodeCount = 0;
    Node *tempHead = other.Head;

    while (tempHead != nullptr) {
      for (nodeCount = 0; nodeCount < tempHead->NumElems; nodeCount++) {
        push_back(tempHead->Elements[nodeCount]);
      }
      tempHead = tempHead->Next;
    }

	}

  //destructor
	~myvector()
	{
    Node *temp = Head;

    while (temp != nullptr) {
      Node *n = temp->Next;
      delete[]temp->Elements;
      delete temp;
      temp = n;
    }

	}

	int size() const
	{
		return NumElems;
	}

	int capacity() const
	{
		// TODO: not yet implemented, return how many elements we can store
		// given the current # of nodes in the linked-list
    Node *temp = Head;
    int count = 0;

    while (temp != nullptr) {
      for (int i = 0; i < NumNodes; i++) {
        count += temp->NodeSize;
        temp = temp->Next;
      }
    }
    return count;
	}

	int nodes() const
	{
    return NumNodes;
	}

	void push_back(const T&e)
	{
		// TODO: needs to be generalized to link on a new node when
		// the current node becomes filled:

		if ((Tail->NumElems) == (Tail->NodeSize)) {
      Node *n = new Node(Tail->NumElems * 2);
      Tail->Next = n;
      Tail = Tail->Next;
      NumNodes++;
		}

		Tail->push_back(e);
		NumElems++;
	}

	T& operator[](int i)
	{
		// TODO: not yet implemented, return ith element. Assume i is valid.
    int nodeNum = 1;
    int count = i;
    int elemCount = 4;
    Node *temp = Head;
    int sizeDoubler = elemCount;
    int preIterCount = elemCount;

    if (i < 4) {
      return temp->Elements[i];
    }
    else {
      while ((elemCount - 1) < i) {
        nodeNum++;
        sizeDoubler = sizeDoubler * 2;
        preIterCount = i;
        count = i - elemCount;
        elemCount = elemCount + sizeDoubler;
        temp = temp->Next;
      }
      return temp->Elements[count];
    }

	}

	T& front()
	{
		// Return first element (this working code):
		return Head->Elements[0];
	}

	T& back()
	{
		// Return last element (this is working code):
		return Tail->Elements[Tail->NumElems - 1];
	}

	iterator begin()
	{
	  return iterator(Head,0);
	}

	iterator end()
	{
    if ( (Tail->NodeSize) == (Tail->NumElems) ) {
      return iterator(Tail->Next, 0);
    }

    return iterator(Tail, Tail->NumElems);
	}
};//End of myvector class

