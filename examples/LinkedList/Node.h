// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.h 
    Listing 4-1 */
#ifndef NODE_
#define NODE_

#include <memory>

template<class ItemType>
class Node
{
private:
   ItemType        item; // A data item
   std::shared_ptr<Node<ItemType>> next; // Pointer to next node
   
public:
   Node() {   };
   Node(const ItemType& anItem) {  item = anItem; };
   Node(const ItemType& anItem, std::shared_ptr<Node<ItemType>> nextNodePtr) { 
   	item = anItem;
   	next = nextNodePtr;
   };
   void setItem(const ItemType& anItem) { item = anItem; };
   void setNext(std::shared_ptr<Node<ItemType>> nextNodePtr) { next = nextNodePtr; };
   ItemType getItem() const { return item; };
   auto getNext() const { return next; };

}; // end Node

#endif
