#include "PlainBox.h"

template <class ItemType>
PlainBox::PlainBox()
{
} // default constructor

template <class ItemType>
PlainBox::PlainBox(const ItemType& theItem) : item(theItem)
{
    item = theItem;
} // end constructor 
template <class ItemType>
virtual void PlainBox::setItem(const ItemType& theItem) 
{
    item = theItem;
}
template <class ItemType>
void PlainBox::getItem(ItemType& theItem) const
{
    return item;
}

// To instantiate object
// PlainBox<double> someBox;
// PlainBox<std::string> stringBox;