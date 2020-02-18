//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Listing C2-4
 @file PlainBox.h */
    
#ifndef _PLAIN_BOX
#define _PLAIN_BOX

template<class ItemType>  // Indicates this is a template
                          // Declaration for the class PlainBox
class PlainBox
{
private:
   // Data field
   ItemType item;
   
public:
   // Default constructor
   PlainBox();
   
   // Parameterized constructor
   PlainBox(const ItemType& theItem);
   
   // Mutator method that can change the value of the data field
   virtual void setItem(const ItemType& theItem);
   
   // Accessor method to get the value of the data field
   virtual ItemType getItem() const;
}; // end PlainBox


template<class ItemType>
PlainBox<ItemType>::PlainBox()
{
} // end default constructor

template<class ItemType>
PlainBox<ItemType>::PlainBox(const ItemType& theItem)
{
    item = theItem;
} // end constructor

template<class ItemType>
void PlainBox<ItemType>::setItem(const ItemType& theItem)
{
    item = theItem;
} // end setItem

template<class ItemType>
ItemType PlainBox<ItemType>::getItem() const
{
    return item;
} // end getItem

#endif
