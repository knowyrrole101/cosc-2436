// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT sorted list using ADT list.
 Listing 12-5.
 @file SortedListAsA.h */

#ifndef _SORTED_LIST_AS_A
#define _SORTED_LIST_AS_A

#include <memory>
#include "SortedListInterface.h"
#include "LinkedList.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class SortedListAsA : public SortedListInterface<ItemType>, private LinkedList<ItemType>
{
public:
   SortedListAsA();
   SortedListAsA(const SortedListAsA<ItemType>& sList);
   virtual ~SortedListAsA();

   bool insertSorted(const ItemType& newEntry) override;
   bool removeSorted(const ItemType& anEntry) override;
   int getPosition(const ItemType& newEntry) const override;
   
   // The following methods are inherited and have the same 
   // specifications as given in ListInterface:
   bool isEmpty() const override;
   int getLength() const override;
   bool remove(int position) override;
   void clear() override;
   ItemType getEntry(int position) const override;
}; // end SortedListAsA



template<class ItemType>
SortedListAsA<ItemType>::SortedListAsA()
{
}  // end default constructor

template<class ItemType>
SortedListAsA<ItemType>::SortedListAsA(const SortedListAsA<ItemType>& sList)
:LinkedList<ItemType>(static_cast<LinkedList<ItemType>>(sList))
{
    
}  // end copy constructor

template<class ItemType>
SortedListAsA<ItemType>::~SortedListAsA()
{
    clear();
}  // end destructor

template<class ItemType>
bool SortedListAsA<ItemType>::insertSorted(const ItemType& newEntry)
{
    int newPosition = abs(getPosition(newEntry));
    return LinkedList<ItemType>::insert(newPosition, newEntry);
}  // end insertSorted

template<class ItemType>
bool SortedListAsA<ItemType>::removeSorted(const ItemType& anEntry)
{
    bool ableToDelete = false;
    // if (!this->isEmpty())
    if (!LinkedList<ItemType>::isEmpty())
    {
        int position = getPosition(anEntry);
        
        ableToDelete = position > 0;
        if (ableToDelete)
        {
            ableToDelete = LinkedList<ItemType>::remove(position);
            //       ableToDelete = this->remove(position);
        }  // end if
    }  // end if
    
    return ableToDelete;
}  // end removeSorted

template<class ItemType>
int SortedListAsA<ItemType>::getPosition(const ItemType& anEntry) const
{
    int position = 1;
    int length = LinkedList<ItemType>::getLength();
    // int length = this->getLength();
    
    // while ( (position <= length) && (anEntry > this->getEntry(position)) )
    while ( (position <= length) &&
           (anEntry > LinkedList<ItemType>::getEntry(position)) )
    {
        position++;
    }  // end while
    
    // if ( (position > length) || (anEntry != this->getEntry(position)) )
    if ( (position > length) ||
        (anEntry != LinkedList<ItemType>::getEntry(position)) )
    {
        position = -position;
    }  // end if
    
    return position;
}  // end getPosition

//=====================
// List operations:
template<class ItemType>
void SortedListAsA<ItemType>::clear()
{
    LinkedList<ItemType>::clear();
}  // end clear


template<class ItemType>
bool SortedListAsA<ItemType>::isEmpty() const
{
    return LinkedList<ItemType>::isEmpty();
}  // end isEmpty

template<class ItemType>
int SortedListAsA<ItemType>::getLength() const
{
    return LinkedList<ItemType>::getLength();
}  // end getLength

template<class ItemType>
bool SortedListAsA<ItemType>::remove(int position)
{
    return LinkedList<ItemType>::remove(position);
}

template<class ItemType>
ItemType SortedListAsA<ItemType>::getEntry(int position) const
{
    return LinkedList<ItemType>::getEntry(position);
}

#endif 
