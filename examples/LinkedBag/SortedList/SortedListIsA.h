// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT sorted list using ADT list.
 Listing 12-4.
 @file SortedListIsA.h */

#ifndef _SORTED_LIST_IS_A
#define _SORTED_LIST_IS_A

#include <memory>
#include "LinkedList.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class SortedListIsA : public LinkedList<ItemType>// , public SortedListInterface<ItemType>
{
public:
   SortedListIsA();
   SortedListIsA(const SortedListIsA<ItemType>& sList);
   virtual ~SortedListIsA();

   bool insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& anEntry) const;
   
   // The inherited methods remove, clear, getEntry, isEmpty, and
   // getLength have the same specifications as given in ListInterface.
/*
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);
   bool isEmpty() const;
   int getLength() const;
*/
   // The following methods must be overridden to disable their
   // effect on a sorted list:
   bool insert(int newPosition, const ItemType& newEntry) override;
	void replace(int position, const ItemType& newEntry) override;
}; // end SortedListIsA


template<class ItemType>
SortedListIsA<ItemType>::SortedListIsA()
{
}  // end default constructor

template<class ItemType>
SortedListIsA<ItemType>::SortedListIsA(const SortedListIsA<ItemType>& sList)
:LinkedList<ItemType>(sList)
{
}  // end copy constructor

template<class ItemType>
SortedListIsA<ItemType>::~SortedListIsA()
{
}  // end destructor

template<class ItemType>
bool SortedListIsA<ItemType>::insertSorted(const ItemType& newEntry)
{
    int newPosition = std::abs(getPosition(newEntry));
    
    // We need to call the LinkedList version here since the
    // SortedListIsA version does nothing but return false
    LinkedList<ItemType>::insert(newPosition, newEntry);
    // this->insert(newPosition, newEntry); // WRONG as it calls the overriding version
    return true;
}  // end insertSorted

template<class ItemType>
bool SortedListIsA<ItemType>::removeSorted(const ItemType& anEntry)
{
    int position = getPosition(anEntry);
    bool ableToRemove = position > 0;
    
    if (ableToRemove)
    {
        ableToRemove = LinkedList<ItemType>::remove(position);
    }  // end if
    
    return ableToRemove;
}  // end removeSorted

template<class ItemType>
int SortedListIsA<ItemType>::getPosition(const ItemType& anEntry) const
{
    int position = 1;
    int length = LinkedList<ItemType>::getLength();
    
    while ( (position <= length) &&
           (anEntry > LinkedList<ItemType>::getEntry(position)) )
    {
        position++;
    }  // end while
    
    if ( (position > length) ||
        (anEntry != LinkedList<ItemType>::getEntry(position)) )
    {
        position = -position;
    }  // end if
    
    return position;
}  // end getPosition

template<class ItemType>
bool SortedListIsA<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
    return false;
} // end insert

template<class ItemType>
void SortedListIsA<ItemType>::replace(int position, const ItemType& newEntry)
{
    throw PrecondViolatedExcep("This is an illegal action!");
} // end replace


#endif 
