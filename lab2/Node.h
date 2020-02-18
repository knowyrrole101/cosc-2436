#ifndef NODE_
#define NODE_

template<class ItemType>
class Node
{
    private:
        ItemType item; // Item Attribute
        Node<ItemType> *next; // Pointer Attribute to next Item
    public:
        Node();
        Node(const ItemType &anItem); 
        Node(const ItemType &anItem, Node<ItemType> *nextNodePtr);

        // Setter Methods
        void setItem(const ItemType &anItem);
        void setNext(Node<ItemType> *nextNodePtr);

        // Getter Methods
        ItemType getItem() const;
        Node<ItemType> *getNext() const;
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
} 

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{   
} 

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType> *nextNodePtr) : item(anItem), next(nextNodePtr)
{
}

template<class ItemType>
Node<ItemType>::setItem(const ItemType &anItem)
{
    item = anItem;
}

template<class ItemType>
Node<ItemType>::setNext(Node<ItemType> *nextNodePtr)
{
    next = nextNodePtr;
}

template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
    return item;
} 

template<class ItemType>
Node<ItemType> *Node<ItemType>::getNext() const
{
    return next;
}

#endif