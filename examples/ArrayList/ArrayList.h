// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT list: Array-based implementation.
    Listing 9-1.
    @file ArrayList.h */

#ifndef ARRAY_LIST_
#define ARRAY_LIST_

#include "ListInterface.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class ArrayList : public ListInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 5; // Small capacity to test for a full list 
	ItemType items[DEFAULT_CAPACITY+1];      // Array of list items (not using element [0]
   int itemCount;                         // Current count of list items 
   int maxItems;                          // Maximum capacity of the list
   
public:
   ArrayList();
   // Copy constructor and destructor are supplied by compiler
   
   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();
   
   /** @throw PrecondViolatedExcep if position < 1 or position > getLength(). */
   ItemType getEntry(int position) const;

   /** @throw PrecondViolatedExcep if position < 1 or position > getLength(). */
   void replace(int position, const ItemType& newEntry);
}; // end ArrayList



template<class ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int ArrayList<ItemType>::getLength() const
{
    return itemCount;
}  // end getLength

template<class ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    bool ableToInsert = (newPosition >= 1)
    && (newPosition <= itemCount + 1)
    && (itemCount < maxItems);
    if (ableToInsert)
    {
        // Make room for new entry by shifting all entries at
        // positions >= newPosition toward the end of the array
        // (no shift if newPosition == itemCount + 1)
        for (int entryPosition = itemCount; entryPosition >= newPosition; entryPosition--)
            items[entryPosition + 1] = items[entryPosition]; // copy the entry right
        
        // Insert new entry
        items[newPosition] = newEntry;
        itemCount++;  // Increase count of entries
    }  // end if
    
    return ableToInsert;
}  // end insert

template<class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
    bool ableToRemove = (position >= 1) && (position <= itemCount);
    if (ableToRemove)
    {
        // Remove entry by shifting all entries after the one at
        // position toward the beginning of the array
        // (no shift if position == itemCount)
        for (int entryPosition = position; entryPosition < itemCount; entryPosition++)
            items[entryPosition] = items[entryPosition + 1]; // copy entry on the right to left
        
        itemCount--;  // Decrease count of entries
    }  // end if
    
    return ableToRemove;
}  // end remove

template<class ItemType>
void ArrayList<ItemType>::clear()
{
    itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const
{
    // Enforce precondition
    bool ableToGet = (position >= 1) && (position <= itemCount);
    if (ableToGet)
    {
        return items[position];
    }
    else
    {
        std::string message = "getEntry() called with an empty list or ";
        message  = message + "invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end getEntry

template<class ItemType>
void ArrayList<ItemType>::replace(int position, const ItemType& newEntry)
{
    // Enforce precondition
    bool ableToSet = (position >= 1) && (position <= itemCount);
    if (ableToSet)
    {
        items[position] = newEntry;
    }
    else
    {
        std::string message = "replace() called with an empty list or ";
        message  = message + "invalid position.";
        throw(PrecondViolatedExcep(message));
    }  // end if
}  // end replace

#endif 
