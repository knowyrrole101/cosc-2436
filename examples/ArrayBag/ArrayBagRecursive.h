//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Header file for an array-based implementation of the ADT bag.
 @file ArrayBag.h */

#ifndef ARRAY_BAG_RECURSIVE_
#define ARRAY_BAG_RECURSIVE_

#include <cstddef>
#include "BagInterface.h"

template<class ItemType>
class ArrayBagRecursive : public BagInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 6; // Small size to test for a full bag
	ItemType items[DEFAULT_CAPACITY];      // Array of bag items
   int itemCount;                         // Current count of bag items 
   int maxItems;                          // Max capacity of the bag
   
   // Returns either the index of the element in the array items that
   // contains the given target or -1, if the array does not contain 
   // the target.
   int getIndexOf(const ItemType& target, int searchIndex) const;
   
   
   int countFrequency(const ItemType& anEntry, int searchIndex) const;

public:
	ArrayBagRecursive();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
   std::vector<ItemType> toVector() const;
}; // end ArrayBag




template<class ItemType>
ArrayBagRecursive<ItemType>::ArrayBagRecursive(): itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
int ArrayBagRecursive<ItemType>::getCurrentSize() const
{
    return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool ArrayBagRecursive<ItemType>::isEmpty() const
{
    return itemCount == 0;
}  // end isEmpty

template<class ItemType>
bool ArrayBagRecursive<ItemType>::add(const ItemType& newEntry)
{
    bool hasRoomToAdd = (itemCount < maxItems);
    if (hasRoomToAdd)
    {
        items[itemCount] = newEntry;
        itemCount++;
    }  // end if
    
    return hasRoomToAdd;
}  // end add

template<class ItemType>
bool ArrayBagRecursive<ItemType>::remove(const ItemType& anEntry)
{
    int locatedIndex = getIndexOf(anEntry, 0);
    bool canRemoveItem = !isEmpty() && (locatedIndex > -1);
    if (canRemoveItem)
    {
        itemCount--;
        items[locatedIndex] = items[itemCount];
    }  // end if
    
    return canRemoveItem;
}  // end remove

template<class ItemType>
void ArrayBagRecursive<ItemType>::clear()
{
    itemCount = 0;
}  // end clear

template<class ItemType>
bool ArrayBagRecursive<ItemType>::contains(const ItemType& anEntry) const
{
    return getIndexOf(anEntry, 0) > -1;
}  // end contains

template<class ItemType>
int ArrayBagRecursive<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
    return countFrequency(anEntry, 0);
}  // end getFrequencyOf

template<class ItemType>
std::vector<ItemType> ArrayBagRecursive<ItemType>::toVector() const
{
    std::vector<ItemType> bagContents;
    for (int i = 0; i < itemCount; i++)
        bagContents.push_back(items[i]);
    
    return bagContents;
}  // end toVector

// private
template<class ItemType>
int ArrayBagRecursive<ItemType>::countFrequency(const ItemType& anEntry, int searchIndex) const
{
    int frequency = 0;
    if (searchIndex < itemCount)
    {
        if (items[searchIndex] == anEntry)
        {
            frequency = 1 + countFrequency(anEntry, searchIndex + 1);
        }
        else
        {
            frequency = countFrequency(anEntry, searchIndex + 1);
        }  // end if
    }  // end if
    
    return frequency;
}  // end countFrequency

// private
template<class ItemType>
int ArrayBagRecursive<ItemType>::getIndexOf(const ItemType& target, int searchIndex) const
{
    int result = -1;
    if (searchIndex < itemCount)
    {
        if (items[searchIndex] == target)
        {
            result = searchIndex;
        }
        else
        {
            result = getIndexOf(target, searchIndex + 1);
        }  // end if
    }  // end if
    
    return result;
}  // end getIndexOf

#endif
