#ifndef LINKED_SORTED_LIST_
#define LINKED_SORTED_LIST_

#include <memory>
#include "SortedListInterface.h"
#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
   std::shared_ptr<Node<ItemType>> headPtr; 
   int itemCount;           
   auto getNodeBefore(const ItemType& anEntry) const;
   auto getNodeAt(int position) const;
   auto copyChain(const std::shared_ptr<Node<ItemType>>& origChainPtr);
   
public:
   LinkedSortedList();
   LinkedSortedList(const LinkedSortedList<ItemType>& aList);
   virtual ~LinkedSortedList();   
   bool insertSorted(const ItemType& newEntry);
   bool removeSorted(const ItemType& anEntry);
   int getPosition(const ItemType& newEntry) const;
   bool isEmpty() const;
   int getLength() const;
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);
}; 

#include "LinkedSortedList.cpp"
#endif