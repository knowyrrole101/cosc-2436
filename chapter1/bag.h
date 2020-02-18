#ifndef BAG_INTERFACE
#define BAG_INTERFACE

#include <vector>
using namespace std;

template<class ItemType>

// Abstract and Base Class - Base class is not inherited - Abstract uses virtual and overridable
class BagInterface
{   
    //attributes up top.

    public:
        // virtual enables polymorphism - only in c++
        virtual int getCurrentSize() const = 0;
        // By value memory hit so use pass by reference - Const and pass by reference so it cant be modified.
        virtual bool add(const ItemType& newEntry) = 0;
        virtual std::vector<ItemType> toVector() const=0;
        // Clean up
        virtual ~BagInterface () {}
    
};
#endif