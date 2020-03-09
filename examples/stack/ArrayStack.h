//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_EXCEPTIONS
#define ARRAY_STACK_EXCEPTIONS

#include "StackInterface.h"
#include "PrecondViolatedExcep.h"

const int MAX_STACK = 5;

template<class ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:
	ItemType items[MAX_STACK]; // Array of stack items
	int      top;              // Index to top of stack
	
public:
	 ArrayStack();
	 bool isEmpty() const;
	 bool push(const ItemType& newEntry);
	 bool pop();
	 ItemType peek() const;	
}; // end ArrayStack


template<class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1)
{
}  // end default constructor

// Copy constructor and destructor are supplied by the compiler

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
    return top < 0;
}  // end isEmpty

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
    bool result = false;
    if (top < MAX_STACK - 1)
    {
        // Stack has room for another item
        top++;
        items[top] = newEntry;
        result = true;
    }  // end if
    
    return result;
}  // end push


template<class ItemType>
bool ArrayStack<ItemType>::pop()
{
    bool result = false;
    if (!isEmpty())
    {
        result = true;
        top--;
    }  // end if
    
    return result;
}  // end pop


template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
    // Enforce precondition
    if (isEmpty())
        throw PrecondViolatedExcep("peek() called with empty stack");
        
        // Stack is not empty; return top
        return items[top];
}  // end peek



#endif
