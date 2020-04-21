
// Linked List Header File
#include "LinkedSortedList.h"  // Header file
// Assertions
#include <cassert>

using namespace std;

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() : headPtr(nullptr), itemCount(0)
{
}  

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList)
{
	headPtr = copyChain(aList.headPtr);
   itemCount = aList.itemCount;
}  

template<class ItemType>
auto LinkedSortedList<ItemType>::copyChain(const shared_ptr<Node<ItemType>>& origChainPtr)
{
   shared_ptr<Node<ItemType>> copiedChainPtr;
	if (origChainPtr != nullptr)
	{
      // Copy Original
      copiedChainPtr = make_shared<Node<ItemType>>(origChainPtr->getItem());
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));		
	} 
   return copiedChainPtr;
}  

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
   clear();
}  

template<class ItemType>
bool LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
   auto newNodePtr = make_shared<Node<ItemType>>(newEntry); 
   auto prevPtr = getNodeBefore(newEntry);
   
   if (isEmpty() || (prevPtr == nullptr)) 
   {
      newNodePtr->setNext(headPtr);
      headPtr = newNodePtr;
   }
   else 
   {
      auto aftPtr = prevPtr->getNext();
      newNodePtr->setNext(aftPtr);
      prevPtr->setNext(newNodePtr);
   } 
   
   itemCount++;
   return true;
} 

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& anEntry)
{
   bool ableToDelete = false;
   if (!isEmpty())
   {
      auto nodeToRemovePtr = headPtr;
      auto prevPtr = getNodeBefore(anEntry);
      if (prevPtr != nullptr)
         nodeToRemovePtr = prevPtr->getNext();
       
      ableToDelete = (nodeToRemovePtr != nullptr) && 
                     (anEntry == nodeToRemovePtr->getItem());
      if (ableToDelete)
      {
         auto aftPtr = nodeToRemovePtr->getNext();
         if (nodeToRemovePtr == headPtr)
         {
            headPtr = aftPtr;
         }
         else
         {
            prevPtr->setNext(aftPtr);
         }  
         
         itemCount--;  
      }  
   }  
   return ableToDelete;
}  

template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType& anEntry) const
{
   int position = 1;
   auto curPtr = headPtr;
   
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
      curPtr = curPtr->getNext();
      position++;
   } 
   
   if ( (curPtr == nullptr) || (anEntry != curPtr->getItem()) )
      position = -position;
   
   return position;
}  

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
{
   bool ableToDelete = (position >= 1) && (position <= itemCount);
   if (ableToDelete)
   {
      if (position == 1)
      {  
         headPtr = headPtr->getNext();
      }
      else
      {
         auto prevPtr = getNodeAt(position - 1);
         auto curPtr = prevPtr->getNext();
         prevPtr->setNext(curPtr->getNext());
      }  
      
      itemCount--;  
   }  
   
   return ableToDelete;
}  

template<class ItemType>
void LinkedSortedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      auto nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }
}  

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
   return itemCount;
}  

template<class ItemType>
auto LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
   auto curPtr = headPtr;
   shared_ptr<Node<ItemType>> prevPtr; 
   while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) )
   {
      prevPtr = curPtr;
      curPtr = curPtr->getNext();
   }  
   return prevPtr;
} 

template<class ItemType>
auto LinkedSortedList<ItemType>::getNodeAt(int position) const
{
   assert((position >= 1) && (position <= itemCount));
   auto curPtr = headPtr;
   for (int skipNodePtr = 1; skipNodePtr < position; skipNodePtr++)
      curPtr = curPtr->getNext();
   
   return curPtr;
} 