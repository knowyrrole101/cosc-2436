#include <iostream>
#include <string>

using namespace std;

class Node {
    private:
        char item;
        Node * next; 

    public:
        // Constructor
        Node() : next(nullptr) {}
        Node(char item) : item(item), next(nullptr) {} 

        char getItem() const 
        {
            return item;
        }

        void setItem(char someItem)
        {
            Node::item = someItem;
        }

        Node *getNext() const 
        {
            return next;
        }

        void setNext(Node *next){
            Node::next = next;
        }
};

class LinkedChar
{
    private:
        Node *head;
        int nodeCount;    

    public:
        LinkedChar() : head(nullptr){};
        LinkedChar(string someString) : head(nullptr)
        {   
            // Node *currNode = head;
            // currNode = new Node(someString[2]);
            for(int i=0; i < someString.size(); i++)
            {   
                Node *currNode = head;
                while(currNode!=nullptr)
                {   
                    currNode = currNode->getNext();
                }
                currNode = new Node(someString[i]);
                nodeCount++;
                cout << i << ": ";
                cout << currNode->getItem() << endl;
            };
        };

        // Returns First Instance of char in linked list
        int index(char &item) const
        {   
            Node *currNode = head;
            // Index Counter
            int count = 0;
            // Traverse Node
            while(currNode!=nullptr && currNode->getItem()!= item)
            {   
                currNode = currNode->getNext();
                count++;
            }
            if(currNode->getItem()==item){
                return count++;
            }
            return -1;
        }

        // Returns length of linked list
        int length()
        {   
            // Doesnt count break 
            return nodeCount-1;
        }
        
        void append(const LinkedChar &lc)
        {
            cout << "Test0" << endl;
        }

        bool submatch(const LinkedChar &lc) const
        {
            return true;
        }


        void clear()
        {   
            Node *currNode = head;
            while(currNode !=nullptr)
            {
                Node *deleteNode = currNode;
                currNode = currNode->getNext();
                delete deleteNode;
            }
        }

        ~LinkedChar()
        {
            clear();
        }

};

int main()
{   
    string someString = "hello";

    // Initialize Linked List and Pass in String
    LinkedChar someChars;
    someChars = LinkedChar(someString);
    // Get Length of Linked List
    cout << someChars.length() << endl;
    someChars.~LinkedChar();

}