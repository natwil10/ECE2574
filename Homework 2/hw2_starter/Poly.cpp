/////////////////////////////////////////////////////////////
//  HW2 -- starter - ALA 2/2018

/** Implementation file for the class Poly.
 @file Poly.cpp */

#include "Poly.h"
#include "Node.h"
#include <cstddef>
#include <iostream>
#include <cmath>

using namespace std;

// TO-DO: Implement the default constructor here.
template<class ItemType>
Poly<ItemType>::Poly() : headPtr(nullptr), pointCount(0)
{
}  // end default constructor

// TO-DO: Implement the copy constructor here.
template<class ItemType>
Poly<ItemType>::Poly(const Poly<ItemType>& aPoly)
{
	pointCount = aPoly.pointCount;
	Node<ItemType> *origChainPtr = aPoly.headPtr;
	
	if (origChainPtr == nullptr)
	{
		headPtr = nullptr;
	}

	else
	{
		headPtr = new Node<ItemType>();

		headPtr->setX(origChainPtr->getX());
		headPtr->setY(origChainPtr->getY());

		origChainPtr = origChainPtr->getNext();

		Node<ItemType> *newChainPtr = headPtr;
		while (origChainPtr != nullptr)
		{
		
			Node<ItemType> *newNodePtr = new Node<ItemType>(origChainPtr->getX(), origChainPtr->getY());

			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();

			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
	
} // end copy constructor

// TO-DO: Implement the isEmpty method here.
template<class ItemType>
bool Poly<ItemType>::isEmpty() const
{

	return (headPtr == nullptr);
	
}  // end isEmpty

// TO-DO: Implement the getNumberOfPoints method here.
template<class ItemType>
int Poly<ItemType>::getNumberOfPoints() const
{
	return pointCount;
}  // end getNumberOfPoints

// TO-DO: Implement the insert method here.  The method must
// insert a node at location 'index', as described in the HW specification.
// No nodes are deleted. If index == 0, then the new node becomes the head node.
// If index == pointCount, then the new node is appended to the tail of the linked list.
template<class ItemType>
bool Poly<ItemType>::insert(const ItemType x, const ItemType y, int index)
{
	if (index > pointCount || index < 0)
	{
		return false;
	}

	Node<ItemType> *node = new Node<ItemType>(x,y);

	
	if (index == 0)
	{
		node->setNext(headPtr);
		headPtr = node;
	}
	else
	{
		node->setNext(getPointerTo(index));
		getPointerTo(index - 1)->setNext(node);
	}

	++pointCount;
	return true;
	
}  // end add

// TO-DO: Implement the remove method here. 
// The node at location 'index', as described in the HW specification, must be removed.
template<class ItemType>
bool Poly<ItemType>::remove(const int index)
{
	if (index >= pointCount || index < 0 || isEmpty())
	{
		return false;
	}
	auto temp = headPtr;
	if (index == 0)
	{
		headPtr = headPtr->getNext();
	}
	else
	{
		temp = getPointerTo(index);
		getPointerTo(index - 1)->setNext(temp->getNext());
	}

	--pointCount;
	delete temp;
	return true;


}  // end remove

// TO-DO: Implement the clear method here. 
template<class ItemType>
void Poly<ItemType>::clear()
{
	while (!isEmpty())		//removes points until the polyline is empty
		remove(0);

}  // end clear

// TO-DO: Implement the getCoordinateX method here.
// If index is not valid, return -1 (instead of raising an exception).
template<class ItemType>
ItemType Poly<ItemType>::getCoordinateX(const int index) const
{
	if (isEmpty() || index < 0 || index >= pointCount)    //returns -1 if the index is invalid
		return -1;

	Node<ItemType> *temp = headPtr;		//creates a pointer to the headpointer of the object being executed

	
	for (int c = 0; c < index; c++)		//traverses the polyline until it reaches the desired index
	{
		temp = temp->getNext();
	}
		return temp->getX();		//returns the x coordinate contained by the node at the desired coordinate


}

// TO-DO: Implement the getCoordinateY method here.
// If index is not valid, return -1 (instead of raising an exception).
template<class ItemType>
ItemType Poly<ItemType>::getCoordinateY(const int index) const
{
	if (isEmpty() || index < 0 || index >= pointCount)	//returns -1 if the index is invalid
		return -1;

	Node<ItemType> *temp = headPtr;	//creates a pointer to the headpointer of the object being executed

	
	for (int c = 0; c < index; c++)	//traverses the polyline until it reaches the desired index
	{
		temp = temp->getNext();
	}
	return temp->getY();	//returns the y coordinate contained by the node at the desired coordinate
}

// TO-DO: Implement the getArcLength method here.
template<class ItemType>
double Poly<ItemType>::getArcLength() const
{
	double sum = 0.0;		//initializes the sum variable to be returned
	double x, y;	//x and y will hold the change in x and change in y between each set of adjacent points on the polyline

	if (!isEmpty() && pointCount > 1)	//traverses the polyline and calculates the distance between each set of adjacent points
	{
		for (int c = 0; c < pointCount-1; c++)
		{
			x = getCoordinateX(c) - getCoordinateX(c+1);
			y = getCoordinateY(c) - getCoordinateY(c+1);

			sum = sum + sqrt(pow((x), 2.0) + pow((y), 2.0));	//executes the distance formula
		}
	}
	return sum;		//returns the arc length of the polyline
}

// TO-DO: Implement the translate method here.
template<class ItemType>
bool Poly<ItemType>::translate(const ItemType deltaX, const ItemType deltaY)
{
	if(isEmpty())		//returns false if the polyline has no points to translate
		return false;

	for (auto temp = headPtr; temp != nullptr; temp = temp->getNext())	//traverses the polyline, changing each coordinate to a value that implements the translation
	{
		temp->setX(temp->getX() + deltaX);
		temp->setY(temp->getY() + deltaY);
	}
	
	return true;	//returns true if the method executes

}

// TO-DO: Implement the destructor here
template<class ItemType>
Poly<ItemType>::~Poly()
{
	clear();	//calls the clear method to delete allocated memory
}


////////////////////////////////////////////////////////////////////////////////////
// overloaded operators

// TO-DO: Implement the operator+ method here
template<class ItemType>
Poly<ItemType>& Poly<ItemType>::operator+(const Poly<ItemType>& rightHandSide) const
{
	//code structure from class slides

	static Poly<ItemType> resultValue;		//declares a polyline that will exist for the duration of the program
	resultValue.clear();

	int c = 0;			//global int to index each insertion in the new polyline


	for (int location = 0; location < getNumberOfPoints(); location++)	//inserts each point of the left hand operand into the new polyline
	{
		resultValue.insert(getCoordinateX(location), getCoordinateY(location), c);
		c++;

	}

	for (int location = 0; location < rightHandSide.pointCount; location++)	//inserts each point of the right hand operand into the new polyline
	{
		resultValue.insert(rightHandSide.getCoordinateX(location), rightHandSide.getCoordinateY(location), c);
		c++;
	}
	
	return resultValue; // returns the new polyline
}

// TO-DO: Implement the operator= method here
template<class ItemType>
Poly<ItemType>& Poly<ItemType>::operator=(const Poly<ItemType>& rightHandSide) 
{
	
	if (this != &rightHandSide)		//code structure from class slides:
	{
		this->clear();				//clears the the object being executed

		for (int c = 0; c < rightHandSide.pointCount; c++)
		{
			insert(rightHandSide.getCoordinateX(c), rightHandSide.getCoordinateY(c), c);		//inserts each point from the polyline into the object being executed
		}
	}

	return *this;	//returns the polyline

}

////////////////////////////////////////////////////////////////////////////////////
// private methods

// TO-DO: Implement the getPointerTo method here
template<class ItemType>
Node<ItemType> *Poly<ItemType>::getPointerTo(const int index) const
{
   Node<ItemType> *curPtr = headPtr;	//creates a node that points to the object's head pointer

   for (int c = 0; c < index; c++)		//traverses the linked list until it arrives at the desired index
   {
	   curPtr = curPtr->getNext();
   }

   return curPtr;						//returns a pointer to the desired index
}  // end getPointerTo