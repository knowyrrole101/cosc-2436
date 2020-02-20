#include <iostream>
#include <string>

using namespace std;

class Node {
    private:
        char item;
        Node* next; 

    public:

        Node() : next(nullptr) {}

        Node(char item) : item(item), next(nullptr) {} 

        char getItem() const 
        {
            return item;
        }

        void setItem(char someItem)
        {
            item = someItem;
        }

        Node *getNext() const 
        {
            return next;
        }

        void setNext(Node *nextNode){
            next = nextNode;
        }
};

class LinkedChar
{   
    private:
        Node* head;

    public:
        int nodeCount;

        LinkedChar() 
        { 
            head = nullptr; 
            nodeCount=0;
        }

        LinkedChar(string& someString)
        {   
            // Create Initial head with first char of string 
            head = new Node();
            head->setItem(someString[0]);
            nodeCount = 1;
        
            for(int i=1;i<someString.size();i++)
            {
                Node *currNode = head;
                Node *prevNode;

                while(currNode!=nullptr)
                {   
                    prevNode = currNode;
                    currNode = currNode->getNext();
                } 
                // Create New Node 
                currNode = new Node();
                currNode->setItem(someString[i]);
                // Set Previous Node Next to Current Node
                prevNode->setNext(currNode);
                nodeCount++;
            }
        }
        void setNodeCount()
        {
            nodeCount++;
        }
        void printLinkedChar()
        {   
            Node *currNode = head;
            while(currNode!=nullptr)
            {   
                cout << currNode << ": " << currNode->getItem() << endl;
                currNode = currNode->getNext();
            }
        }

        int index(char &item)
        {   
            Node *currNode = head;
            int count=0;

            while(currNode!=nullptr && currNode->getItem()!=item)
            {
                count++;
                currNode = currNode->getNext();
            }
            if(currNode!=nullptr)
            {
                return count;
            }
            return -1;
        }

        int length(){
            return nodeCount;
        }

        void append(const LinkedChar &lc) {
            Node *currNode = head;
            Node *prevNode;

            while(currNode!=nullptr)
            {   
                prevNode = currNode;
                currNode = currNode->getNext();
            }   

            if(lc.head!=nullptr)
            {   
                // Add LC head to Tail of Linked List
                currNode = new Node(lc.head->getItem());
                prevNode->setNext(currNode);       
                nodeCount++;

                // Traverse LC Linked List and Add to This Linked List
                Node *currNodeLc = lc.head->getNext();
                Node *prevNodeLc;
                while(currNodeLc!=nullptr)
                {   
                    prevNode = currNode;
                    currNode = new Node(currNodeLc->getItem());
                    prevNode->setNext(currNode);
                    nodeCount++;
                    prevNodeLc = currNodeLc;
                    currNodeLc = currNodeLc->getNext();
                }

            }            
        }

        bool submatch(const LinkedChar &lc) const {
            return false;
        }

        void clear()
        {   
            Node *deleteNode;
            while(head!=nullptr) {
                Node *deleteNode = head;
                head = head->getNext();
                delete deleteNode;
            }      
        }

        // Destructor Method Clear Memory for Each Node if Exists
        ~LinkedChar() {
        } 

};


int main()
{   
    
    int userChoice;
    LinkedChar someLinkedList;
    LinkedChar someLinkedList2;
    string userInput;

    do {   
        cout << "Enter a Choice:" << endl;
        cout << "1. Enter New String" << endl;
        cout << "2. Enter New String" << endl;
        cout << "3. Enter New String" << endl;
        cout << "4. Enter New String" << endl;
        cout << "5. Enter New String" << endl;
        cout << "6. Exit " << endl;
        cin >> userChoice;
        
        switch(userChoice){
            case 1: 
                
                cout << "Enter a String and Create a Linked Character List: ";
                cin >> userInput;
                someLinkedList = LinkedChar(userInput);
                break;
            case 2: 
                cout << "Printing the length of Linked Character List: " << someLinkedList.length() << endl;
                break;
            default:
                cout << "Enter a valid response!" << endl;
                break;            
        };
    } while(userChoice!=6);


    string someString = "hello";
    string someString2 = "world";
    char someChar = 'l';
    // Initialize Linked List and Pass in String
    LinkedChar someChars;
    someChars = LinkedChar(someString); 
    cout << "Current Node count: " << someChars.length() << endl;
    // Append Some Linked Char to Another
    someChars.append(someString2);
    cout << "New Node count after append: " << someChars.length() << endl;
    // Print LinkedChars
    someChars.printLinkedChar();
    cout << "Matching letter is index: " << someChars.index(someChar) << endl;
    // Get Index of a matching char in Linked List
    
    cout << "Clearing Memory: " << endl;
    someChars.clear();
    cout << "Done!" << endl;
    return 0;

}