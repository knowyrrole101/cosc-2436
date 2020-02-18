// Pre Process directives
#ifndef PLAIN_BOX_
#define PLAIN_BOX_

template <class ItemType>
// Set the type of data accepted by class
typedef double itemType;

class PlainBox
{
    private:
        // Data Field
        itemType item;
    
    public:
        // Default Constructor
        PlainBox();
        // Parameterized Constructor
        PlainBox(const ItemType& theItem);
        // Method to change the value of the data field
        void setItem(const itemType& theItem);
        // Method to get the value of the data field
        ItemType getItem() const; // Const needed so it cant be changed. Best practice. 

};
#include "PlainBox.cpp"
#endif