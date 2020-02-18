//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation - RECURSIVE VERSION.
    @file LinkedBagRecursive.h 
    Listing 4-3 */
#ifndef LINKED_BAG_RECURSIVE_
#define LINKED_BAG_RECURSIVE_

#include "BagInterface.h"
#include "Node.h"

template<class ItemType>
class LinkedBagRecursive : public BagInterface<ItemType>
{
private:
   Node<ItemType>* headPtr; // Pointer to first node
   int itemCount;           // Current count of bag items
   
   // Fills the vector bagContents with the data in the nodes of
   // the linked chain to which curPtr points.
   void fillVector(std::vector<ItemType>& bagContents, Node<ItemType>* curPtr) const;
   
   // Locates a given entry within this bag.
   // Returns either a pointer to the node containing a given entry or
   // the null pointer if the entry is not in the bag.
   Node<ItemType>* getPointerTo(const ItemType& target,
                                Node<ItemType>* curPtr) const;
   
   // Counts the frequency of occurrence of a given entry in this bag.
   int countFrequency(const ItemType& anEntry, int counter,
                      Node<ItemType>* curPtr) const;

   // Deallocates all nodes assigned to this bag
   void deallocate(Node<ItemType>* nextNodePtr);
   
public:
   LinkedBagRecursive();
   LinkedBagRecursive(const LinkedBagRecursive<ItemType>& aBag); // Copy constructor
   virtual ~LinkedBagRecursive();                       // Destructor should be virtual
   int getCurrentSize() const;
   bool isEmpty() const;
   bool add(const ItemType& newEntry);
   bool remove(const ItemType& anEntry);
   void clear();
   bool contains(const ItemType& anEntry) const;
   int getFrequencyOf(const ItemType& anEntry) const;
   std::vector<ItemType> toVector() const;
}; // end LinkedBagRecursive


/** ADT bag: Link-based implementation - RECURSIVE VERSION. */


template<class ItemType>
LinkedBagRecursive<ItemType>::LinkedBagRecursive() : headPtr(nullptr), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedBagRecursive<ItemType>::LinkedBagRecursive(const LinkedBagRecursive<ItemType>& aBag)
{
    itemCount = aBag.itemCount;
    Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
    
    if (origChainPtr == nullptr)
        headPtr = nullptr;  // Original bag is empty
    else
    {
        // Copy first node
        headPtr = new Node<ItemType>();
        headPtr->setItem(origChainPtr->getItem());
        
        // Copy remaining nodes
        Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
        origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
        
        while (origChainPtr != nullptr)
        {
            // Get next item from original chain
            ItemType nextItem = origChainPtr->getItem();
            
            origChainPtr = origChainPtr->getNext();  // Advance original-chain pointer
            
            // Create a new node containing the next item
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
            
            // Link new node to end of new chain
            newChainPtr->setNext(newNodePtr);
            
            // Advance pointer to new last node
            newChainPtr = newChainPtr->getNext();
        }  // end while
        
        newChainPtr->setNext(nullptr);              // Flag end of chain
    }  // end if
}  // end copy constructor

template<class ItemType>
LinkedBagRecursive<ItemType>::~LinkedBagRecursive()
{
    clear();
}  // end destructor

template<class ItemType>
bool LinkedBagRecursive<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBagRecursive<ItemType>::getCurrentSize() const
{
    return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBagRecursive<ItemType>::add(const ItemType& newEntry)
{
    // Add to beginning of chain: new node references rest of chain;
    // (headPtr is null if chain is empty)
    Node<ItemType>* nextNodePtr = new Node<ItemType>();
    nextNodePtr->setItem(newEntry);
    nextNodePtr->setNext(headPtr);  // New node points to chain
    //   Node<ItemType>* nextNodePtr = new Node<ItemType>(newEntry, headPtr); // alternate code
    
    headPtr = nextNodePtr;          // New node is now first node
    itemCount++;
    
    return true;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedBagRecursive<ItemType>::toVector() const
{
    std::vector<ItemType> bagContents;
    fillVector(bagContents, headPtr);
    return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBagRecursive<ItemType>::remove(const ItemType& anEntry)
{
    Node<ItemType>* entryNodePtr = getPointerTo(anEntry, headPtr);
    bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
    if (canRemoveItem)
    {
        // Copy data from first node to located node
        entryNodePtr->setItem(headPtr->getItem());
        
        // Delete first node
        Node<ItemType>* nodeToDeletePtr = headPtr;
        headPtr = headPtr->getNext();
        
        // Return node to the system
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        
        itemCount--;
    } // end if
    
    return canRemoveItem;
}  // end remove

template<class ItemType>
void LinkedBagRecursive<ItemType>::clear()
{
    deallocate(headPtr);
    headPtr = nullptr;
    itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBagRecursive<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
    return countFrequency(anEntry, 0, headPtr);
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBagRecursive<ItemType>::contains(const ItemType& anEntry) const
{
    return (getPointerTo(anEntry, headPtr) != nullptr);
}  // end contains

/* ALTERNATE 1
 template<class ItemType>
 bool LinkedBagRecursive<ItemType>::contains(const ItemType& anEntry) const
 {
 return getFrequencyOf(anEntry) > 0;
 }
 */
/* ALTERNATE 2
 template<class ItemType>
 bool LinkedBagRecursive<ItemType>::contains(const ItemType& anEntry) const
 {
 bool found = false;
 Node<ItemType>* curPtr = headPtr;
 int i = 0;
 while (!found && (curPtr != nullptr) && (i < itemCount))
 {
 if (anEntry == curPtr-<getItem())
 {
 found = true;
 }
 else
 {
 i++;
 curPtr = curPtr->getNext();
 }  // end if
 }  // end while
 
 return found;
 }  // end contains
 */

// Private Methods:

template<class ItemType>
void LinkedBagRecursive<ItemType>::fillVector(std::vector<ItemType>& bagContents,
                                              Node<ItemType>* curPtr) const
{
    if (curPtr != nullptr)
    {
        bagContents.push_back(curPtr->getItem());
        fillVector(bagContents, curPtr->getNext());
    } // end if
}  // end toVector

template<class ItemType>
Node<ItemType>* LinkedBagRecursive<ItemType>::getPointerTo(const ItemType& target,
                                                           Node<ItemType>* curPtr) const
{
    Node<ItemType>* result = nullptr;
    if (curPtr != nullptr)
    {
        if (target== curPtr->getItem())
            result = curPtr;
        else
            result = getPointerTo(target, curPtr->getNext());
    } // end if
    
    return result;
}  // end getPointerTo

template<class ItemType>
int LinkedBagRecursive<ItemType>::countFrequency(const ItemType& anEntry, int counter,
                                                 Node<ItemType>* curPtr) const
{
    int frequency = 0;
    if ((curPtr != nullptr) && (counter < itemCount))
    {
        if (anEntry == curPtr->getItem())
        {
            frequency = 1 + countFrequency(anEntry, counter + 1, curPtr->getNext());
        }
        else
        {
            frequency = countFrequency(anEntry, counter + 1, curPtr->getNext());
        }  // end if
    } // end while
    
    return frequency;
}  // end countFrequency

template<class ItemType>
void LinkedBagRecursive<ItemType>::deallocate(Node<ItemType>* nextNodePtr)
{
    Node<ItemType>* nodeToDeletePtr = nextNodePtr;
    if (nextNodePtr != nullptr)
    {
        nextNodePtr = nextNodePtr->getNext();
        delete nodeToDeletePtr;
        nodeToDeletePtr = nextNodePtr;
        deallocate(nextNodePtr);
    }  // end if
}  // end deallocate




#endif
