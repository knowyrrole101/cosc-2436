#include <stdexcept>

#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>

class NotFoundException : public std::logic_error

{
public:
   NotFoundException(const std::string& message = "")
   : std::logic_error("Not Found Exception: " + message)
	{
	}
}; // end NotFoundException 


class PrecondViolatedExcep : public std::logic_error
{
public:
   PrecondViolatedExcep(const std::string& message = "")
   : std::logic_error("Precondition Violated Exception: " + message)
	{
	}
}; // end PrecondViolatedExcep 



template<class ItemType>
class BinaryNode
{   
private:
   ItemType              item;           // Data portion
   std::shared_ptr<BinaryNode<ItemType>> leftChildPtr;   // Pointer to left child
   std::shared_ptr<BinaryNode<ItemType>> rightChildPtr;  // Pointer to right child

public:
   BinaryNode();
   BinaryNode(const ItemType& anItem);
   BinaryNode(const ItemType& anItem,
              std::shared_ptr<BinaryNode<ItemType>> leftPtr,
              std::shared_ptr<BinaryNode<ItemType>> rightPtr);

   void setItem(const ItemType& anItem);
   ItemType getItem() const;
   
   bool isLeaf() const;

    std::shared_ptr<BinaryNode<ItemType>> getLeftChildPtr() const;
    std::shared_ptr<BinaryNode<ItemType>> getRightChildPtr() const;
   
   void setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr);
   void setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr);
}; // end BinaryNode

/** @file BinaryNode.cpp */


template<class ItemType>
BinaryNode<ItemType>::BinaryNode()
: item(nullptr), leftChildPtr(nullptr), rightChildPtr(nullptr)
{ }  // end default constructor

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
: item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)
{ }  // end constructor

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
                                 std::shared_ptr<BinaryNode<ItemType>> leftPtr,
                                 std::shared_ptr<BinaryNode<ItemType>> rightPtr)
: item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{ }  // end constructor

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
}  // end setItem

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
    return item;
}  // end getItem

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
    return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr)
{
    leftChildPtr = leftPtr;
}  // end setLeftChildPtr

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr)
{
    rightChildPtr = rightPtr;
}  // end setRightChildPtr

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getLeftChildPtr() const
{
    return leftChildPtr;
}  // end getLeftChildPtr

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getRightChildPtr() const
{
    return rightChildPtr;
}  // end getRightChildPtr





template<class ItemType>
class BinaryTreeInterface
{
public:
   /** Tests whether this binary tree is empty.
    @return True if the binary tree is empty, or false if not. */
   virtual bool isEmpty() const = 0;
   
   /** Gets the height of this binary tree.
    @return The height of the binary tree. */
   virtual int getHeight() const = 0;
   
   /** Gets the number of nodes in this binary tree.
    @return The number of nodes in the binary tree. */
   virtual int getNumberOfNodes() const = 0;
   
   /** Gets the data that is in the root of this binary tree.
    @pre  The binary tree is not empty.
    @post  The root’s data has been returned, and the binary tree is unchanged.
    @return  The data in the root of the binary tree. */
   virtual ItemType getRootData() const = 0;
   
   /** Replaces the data item in the root of this binary tree
       with the given data, if the tree is not empty. However, if
       the tree is empty, inserts a new root node containing the
       given data into the tree.
    @pre  None.
    @post  The data in the root of the binary tree is as given.
    @param newData  The data for the root. */
   virtual void setRootData(const ItemType& newData) = 0;
   
   /** Adds a new node containing the given data to this binary tree.
    @param newData  The data for the new node.
    @post  The binary tree contains a new node.
    @return  True if the addition is successful, or false not. */
   virtual bool add(const ItemType& newData) = 0;
   
   /** Removes the node containing the given data item from this binary tree.
    @param data  The data value to remove from the binary tree.
    @return  True if the removal is successful, or false not. */
   virtual bool remove(const ItemType& data) = 0;
   
   /** Removes all nodes from this binary tree. */
   virtual void clear() = 0;
   
   /** Gets a specific entry in this binary tree.
    @post  The desired entry has been returned, and the binary tree
       is unchanged. If no such entry was found, an exception is thrown.
    @param anEntry  The entry to locate.
    @return  The entry in the binary tree that matches the given entry.
    @throw  NotFoundException if the given entry is not in the tree. */
   virtual ItemType getEntry(const ItemType& anEntry) const
                    throw(NotFoundException) = 0;
   
   /** Tests whether a given entry occurs in this binary tree.
    @post  The binary search tree is unchanged.
    @param anEntry  The entry to find.
    @return  True if the entry occurs in the tree, or false if not. */
   virtual bool contains(const ItemType& anEntry) const = 0;
   
   /** Traverses this binary tree in preorder (inorder, postorder) and
       calls the function visit once for each node.
    @param visit A client-defined function that performs an operation on
       or with the data in each visited node. */
   virtual void preorderTraverse(void visit(ItemType&)) const = 0;
   virtual void inorderTraverse(void visit(ItemType&)) const = 0;
   virtual void postorderTraverse(void visit(ItemType&)) const = 0;
   
   /** Destroys object and frees memory allocated by object. */
   virtual ~BinaryTreeInterface() {  }
   
}; // end BinaryTreeInterface


template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
protected:
   std::shared_ptr<BinaryNode<ItemType>> rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   
   int getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
   int getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const;
   
   // Recursively adds a new node to the tree in a left/right fashion to
   // keep the tree balanced.
   std::shared_ptr<BinaryNode<ItemType>> balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                     std::shared_ptr<BinaryNode<ItemType>> newNodePtr);
   
   // Copies values up the tree to overwrite value in current node until
   // a leaf is reached; the leaf is then removed, since its value is
   // stored in the parent.
   std::shared_ptr<BinaryNode<ItemType>> moveValuesUpTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);
   
   // Removes the target value from the tree by calling moveValuesUpTree
   // to overwrite value with value from child.
   virtual std::shared_ptr<BinaryNode<ItemType>>
               removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                     const ItemType target, bool& success);
   
   // Recursively searches for target value in the tree by using a
   // preorder traversal.
   std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
                                  const ItemType& target,
                                  bool& success) const;
   
   // Copies the tree rooted at treePtr and returns a pointer to
   // the copy.
   std::shared_ptr<BinaryNode<ItemType>> copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const;
   
   // Recursively deletes all nodes from the tree.
   void destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr);
   
   // Recursive traversal helper methods:
   void preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
   void inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
   void postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const;
   
public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   BinaryNodeTree();
   BinaryNodeTree(const ItemType& rootItem);
   BinaryNodeTree(const ItemType& rootItem,
                   const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                   const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr);
   BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
   virtual ~BinaryNodeTree();
   
   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------
   bool isEmpty() const;
   int getHeight() const;
   int getNumberOfNodes() const;
   ItemType getRootData() const throw(PrecondViolatedExcep);
   void setRootData(const ItemType& newData);
   bool add(const ItemType& newData); // Adds a node
   bool remove(const ItemType& data); // Removes a node
   void clear();
   ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
   bool contains(const ItemType& anEntry) const;
   
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   void preorderTraverse(void visit(ItemType&)) const;
   void inorderTraverse(void visit(ItemType&)) const;
   void postorderTraverse(void visit(ItemType&)) const;
   
   //------------------------------------------------------------
   // Overloaded Operator Section.
   //------------------------------------------------------------
   BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
}; // end BinaryNodeTree


/** @file BinaryNodeTree.cpp */

//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()),
                            getHeightHelper(subTreePtr->getRightChildPtr()));
}  // end getHeightHelper

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr())
        + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}  // end getNumberOfNodesHelper

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                                            std::shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
    if (subTreePtr == nullptr)
        return newNodePtr;
    else
    {
        auto leftPtr = subTreePtr->getLeftChildPtr();
        auto rightPtr = subTreePtr->getRightChildPtr();
        
        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
        {
            rightPtr = balancedAdd(rightPtr , newNodePtr);
            subTreePtr->setRightChildPtr(rightPtr );
        }
        else
        {
            leftPtr = balancedAdd(leftPtr, newNodePtr);
            subTreePtr->setLeftChildPtr(leftPtr);
        }  // end if
        
        return subTreePtr;
    }  // end if
}  // end balancedAdd

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::moveValuesUpTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
    auto  leftPtr = subTreePtr->getLeftChildPtr();
    auto  rightPtr = subTreePtr->getRightChildPtr();
    int leftHeight = getHeightHelper(leftPtr);
    int rightHeight = getHeightHelper(rightPtr);
    if (leftHeight > rightHeight)
    {
        subTreePtr->setItem(leftPtr->getItem());
        leftPtr = moveValuesUpTree(leftPtr);
        subTreePtr->setLeftChildPtr(leftPtr);
        return subTreePtr;
    }
    else
    {
        if (rightPtr != nullptr)
        {
            subTreePtr->setItem(rightPtr->getItem());
            rightPtr =moveValuesUpTree(rightPtr);
            subTreePtr->setRightChildPtr(rightPtr);
            return subTreePtr;
        }
        else
        {
            //this was a leaf!
            // value not important
            return nullptr;
        }  // end if
    }  // end if
}  // end moveValuesUpTree

/** Depth-first search of tree for item.
 @param subTreePtr  tree to search.
 @param target  target item to find.
 @param success  communicate to client we found it.
 @returns  A pointer to node containing the item. */
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                                            const ItemType target,
                                                                            bool& success)
{
    if(subTreePtr == nullptr) // not found here
        return subTreePtr;
    
    if (subTreePtr->getItem() == target) // found it
    {
        subTreePtr = moveValuesUpTree(subTreePtr);
        success = true;
        return subTreePtr;
    }
    else
    {
        auto targetNodePtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(targetNodePtr);
        if (!success) // no need to search right subTree
        {
            targetNodePtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
            subTreePtr->setRightChildPtr(targetNodePtr);
        }  // end if
        
        return subTreePtr;
    }  // end if
}  // end removeValue

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
                                                                         const ItemType& target,
                                                                         bool& success) const
{
    if (treePtr == nullptr) // not found here
        return treePtr;
    
    if (treePtr->getItem() == target) // found it
    {
        success = true;
        return treePtr;
    }
    else
    {
        std::shared_ptr<BinaryNode<ItemType>> targetNodePtr = findNode(treePtr->getLeftChildPtr(), target, success);
        if (!success) // no need to search right subTree
        {
            targetNodePtr = findNode(treePtr->getRightChildPtr(), target, success);
        }  // end if
        
        return targetNodePtr;
    }  // end if
}  // end findNode

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const
{
    std::shared_ptr<BinaryNode<ItemType>> newTreePtr;
    
    // Copy tree nodes during a preorder traversal
    if (oldTreeRootPtr != nullptr)
    {
        // Copy node
        newTreePtr = std::make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr);
        newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
    }  // end if
    
    return newTreePtr;
}  // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
    if (subTreePtr != nullptr)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        subTreePtr.reset(); // decrement reference count to node
    }  // end if
}  // end destroyTree

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
    if (treePtr != nullptr)
    {
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        //      visit(treePtr->getItem());
        preorder(visit, treePtr->getLeftChildPtr());
        preorder(visit, treePtr->getRightChildPtr());
    }  // end if
}  // end preorder

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
    if (treePtr != nullptr)
    {
        inorder(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
        inorder(visit, treePtr->getRightChildPtr());
    }  // end if
}  // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
    if (treePtr != nullptr)
    {
        postorder(visit, treePtr->getLeftChildPtr());
        postorder(visit, treePtr->getRightChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(theItem);
    } // end if
}  // end postorder

//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree()
{  }  // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
:rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{  }  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
                                         const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr,
                                         const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
:rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem,
                                                copyTree(leftTreePtr->rootPtr),
                                                copyTree(rightTreePtr->rootPtr)))
{   }  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
    rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
    destroyTree(rootPtr);
}  // end destructor

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////


template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
    return rootPtr == nullptr;
}  // end isEmpty

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
    return getHeightHelper(rootPtr);
}  // end getHeight

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
    return getNumberOfNodesHelper(rootPtr);
}  // end getNumberOfNodes

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
    destroyTree(rootPtr);
    rootPtr.reset();
}  // end clear

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcep)
{
    if (isEmpty())
        throw PrecondViolatedExcep("getRootData() called with empty tree.");
        
        return rootPtr->getItem();
        }  // end getRootData

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem)
{
    if (isEmpty())
        rootPtr = std::make_shared<BinaryNode<ItemType>>(newItem, nullptr, nullptr);
    else
        rootPtr->setItem(newItem);
}  // end setRootData

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
    auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newData);
    rootPtr = balancedAdd(rootPtr, newNodePtr);
    return true;
}  // end add

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target)
{
    bool isSuccessful = false;
    rootPtr = removeValue(rootPtr, target, isSuccessful);
    return isSuccessful;
}  // end remove

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
    bool isSuccessful = false;
    auto binaryNodePtr = findNode(rootPtr, anEntry, isSuccessful);
    
    if (isSuccessful)
        return binaryNodePtr->getItem();
        else
            throw NotFoundException("Entry not found in tree!");
            }  // end getEntry

template<class ItemType>
bool BinaryNodeTree<ItemType>:: contains(const ItemType& anEntry) const
{
    bool isSuccessful = false;
    findNode(rootPtr, anEntry, isSuccessful);
    return isSuccessful;
}  // end contains

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
    preorder(visit, rootPtr);
}  // end preorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
    inorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
    postorder(visit, rootPtr);
}  // end postorderTraverse

//////////////////////////////////////////////////////////////
//      Overloaded Operator
//////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(
                                                              const BinaryNodeTree<ItemType>& rightHandSide)
{
    if (!isEmpty())
        clear();
    this = copyTree(&rightHandSide);
    return *this;
}  // end operator=




template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
	// use this->rootPtr to access the BinaryNodeTree rootPtr

protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	std::shared_ptr<BinaryNode<ItemType>> placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, std::shared_ptr<BinaryNode<ItemType>> newNode);

	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success) override;

	// Removes a given node from a tree while maintaining a
	// binary search tree.
	std::shared_ptr<BinaryNode<ItemType>> removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr);

	// Removes the leftmost node in the left subtree of the node
	// pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType& inorderSuccessor);

	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	// inherits from BinaryNodeTree

	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	void setRootData(const ItemType& newData) const throw(PrecondViolatedExcep);
	bool add(const ItemType& newEntry) override;
	bool remove(const ItemType& anEntry) override;
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException)override;
	bool contains(const ItemType& anEntry) const override;

	void inorderTraverse(void visit(ItemType&)) const override;
	~BinarySearchTree();
}; // end BinarySearchTree


template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const throw(PrecondViolatedExcep)
{
	if (this->rootPtr == nullptr)
		this->rootPtr = std::make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr);
	else
		this->rootPtr->setItem(newData);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
	auto node = std::make_shared<BinaryNode<ItemType>>(newEntry);
	this->rootPtr = placeNode(this->rootPtr, node);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry)
{
	bool done = false;
	this->rootPtr = removeValue(this->rootPtr, anEntry, done);
	return done;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	auto binaryNodePtr = findNode(this->rootPtr, anEntry);

	if (binaryNodePtr != nullptr)
		return binaryNodePtr->getItem();
	else
		throw NotFoundException("No Entry Found");
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	auto binaryNodePtr = findNode(this->rootPtr, anEntry);
	if (binaryNodePtr != nullptr)
		return true;
	return false;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, std::shared_ptr<BinaryNode<ItemType>> newNode)
{
	if (subTreePtr == nullptr)
		return newNode;
	else
	{
		if (subTreePtr->getItem() > newNode->getItem())
		{
			subTreePtr->setLeftChildPtr(placeNode(subTreePtr->getLeftChildPtr(), newNode));
		}
		else
		{
			subTreePtr->setRightChildPtr(placeNode(subTreePtr->getRightChildPtr(), newNode));
		}  // end if

		return subTreePtr;
	}
}

// Removes the given target value from the tree while maintaining a
// binary search tree.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& success)
{
	if (subTreePtr == nullptr)
	{
		success = false;
	}
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		success = true;
	}
	else if (subTreePtr->getItem() > target)
	{
		std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		std::shared_ptr<BinaryNode<ItemType>> tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		subTreePtr->setRightChildPtr(tempPtr);
	}

	return subTreePtr;
}

// Removes a given node from a tree while maintaining a
// binary search tree.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)
{


	if (nodePtr->isLeaf()) {
		return (nodePtr = nullptr);
	}
	else if (nodePtr->getLeftChildPtr() == nullptr)
	{
		std::shared_ptr<BinaryNode<ItemType>> connect = nodePtr->getRightChildPtr();
		nodePtr = nullptr;
		return connect;
	}
	else if (nodePtr->getRightChildPtr() == nullptr)
	{
		std::shared_ptr<BinaryNode<ItemType>> connect = nodePtr->getLeftChildPtr();
		nodePtr = nullptr;
		return connect;
	}
	else
	{
		ItemType node;
		nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr(), node));
		nodePtr->setItem(node);
		return nodePtr;
	}
}

// Removes the leftmost node in the left subtree of the node
// pointed to by nodePtr.
// Sets inorderSuccessor to the value in this node.
// Returns a pointer to the revised subtree.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType& inorderSuccessor)
{
	if (subTreePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = subTreePtr->getItem();
		return removeNode(subTreePtr);
	}
	else
	{
		auto tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
}

// Returns a pointer to the node containing the given value,
// or nullptr if not found.
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr, const ItemType& target) const
{
	if (treePtr == nullptr)
		return nullptr;
	else if (treePtr->getItem() == target)
	{
		return treePtr;
	}

	else if (treePtr->getItem() > target)
		return findNode(treePtr->getLeftChildPtr(), target);
	else
		return findNode(treePtr->getRightChildPtr(), target);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	this->inorder(visit, this->rootPtr);
}  // end inorderTraverse

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	this->destroyTree(this->rootPtr);
}

std::vector<int> theTreeSorted;

void display(int& anItem)
{
	std::cout << anItem << " ";
	theTreeSorted.push_back(anItem);
}

const int N = 21;
int main() {

	//srand(time(0));
	
	BinarySearchTree<int> bst;
	/*insert 21 random numbers (1-100) on the binary search tree using the STL random library*/
	std::cout << "Generate Random Nums!" << std::endl;
	int firstnum;
	int num;
    // Engine for random numbers
	std::mt19937 random_engine(static_cast<std::mt19937::result_type>(std::time(nullptr)));
    // produces integer values evenly distributed across a range
	std::uniform_int_distribution<int> distribution_1_100(1, 100);

	firstnum = distribution_1_100(random_engine);;
	std::cout << firstnum << " ";
	bst.add(firstnum);
	

	for (int i = 0; i < N-1; i++)
	{
		//generate unique numbers
		num = distribution_1_100(random_engine);;
		while (bst.contains(num))
		{
			num = distribution_1_100(random_engine);;
		}
		//add value to bst
		bst.add(num);
		std::cout << num << " ";
		
	}

	/*remove the first number inserted*/
	std::cout << std::endl << "Removing first number: " << firstnum << std::endl;
	bst.remove(firstnum);

	std::cout << firstnum << " removed from the tree.";
	/*and display the tree
	To display just use in order traversal*/
	std::cout << std::endl << "Binary Search Tree now contains: " << std::endl;
    // In order Traverse Display
	bst.inorderTraverse(display);
	std::cout << "\n";
    
	return 0;
}