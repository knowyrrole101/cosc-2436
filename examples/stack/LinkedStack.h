//  Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Link-based implementation.
    Listing 7-x.  
    @file LinkedStack.h */

#ifndef LINKED_STACK_EXCEPTIONS
#define LINKED_STACK_EXCEPTIONS

#include "StackInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

/** ADT stack - Linked implementation. */

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
	
private:
	Node<ItemType>* topPtr; // Pointer to first node in the chain;
                           // this node contains the stack's top

public:
// Constructors and destructor:
	LinkedStack();                                     // Default constructor
	LinkedStack(const LinkedStack<ItemType>& aStack);  // Copy constructor
	virtual ~LinkedStack();                            // Destructor
	
// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType& newItem);
	bool pop();

   /** @throw PrecondViolatedExcep if the stack is empty */
	ItemType peek() const;
}; // end LinkedStack


template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
    // Point to nodes in original chain
    Node<ItemType>* origChainPtr = aStack.topPtr;
    
    if (origChainPtr == nullptr)
        topPtr = nullptr;  // Original stack is empty
    else
    {
        // Copy first node
        topPtr = new Node<ItemType>();
        topPtr->setItem(origChainPtr->getItem());
        
        // Point to last node in new chain
        Node<ItemType>* newChainPtr = topPtr;
        
        // Advance original-chain pointer
        origChainPtr = origChainPtr->getNext();
        
        // Copy remaining nodes
        while (origChainPtr != nullptr)
        {
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
            
            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
            
            // Advance original-chain pointer
            origChainPtr = origChainPtr->getNext();
        }  // end while
        
        newChainPtr->setNext(nullptr);               // Flag end of chain
    }  // end if
}  // end copy constructor

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
    // Pop until stack is empty
    while (!isEmpty())
        pop();
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
    return topPtr == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newEntry)
{
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry, topPtr);
    topPtr = newNodePtr;
    newNodePtr = nullptr;
    
    return true;
}  // end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
    bool result = false;
    if (!isEmpty())
    {
        // Stack is not empty; delete top
        Node<ItemType>* nodeToDeletePtr = topPtr;
        topPtr = topPtr->getNext();
        
        // Return deleted node to system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        
        result = true;
    }  // end if
    
    return result;
}  // end pop

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
    // Enforce precondition
    if (isEmpty())
        throw(PrecondViolatedExcep("peek() called with empty stack."));
    
    // Stack is not empty; return top
    return topPtr->getItem();
}  // end peek


// End of implementation file.


#endif
