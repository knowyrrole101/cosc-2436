/*
    MAMUN AHMED
    COSC 2436 - T/TH - LAB 2 
    LAB 2 - STORED LINKED LIST OF CHARACTERS
    Output: Program should take in strings and parse into 
    Linked List of Characters.
*/

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
        
        ~LinkedChar() {clear();} 

        void printLinkedChar()
        {   
            Node *currNode = head;
            while(currNode!=nullptr)
            {   
                std::cout << currNode << ": " << currNode->getItem() << endl;
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

        bool subStringMatch(const LinkedChar &lc) const
        {
            Node *stringNode = head;
            Node *subStringNode = lc.head;
            int count = 0;
            if(subStringNode!=nullptr){
              while(stringNode!=nullptr)
                {   
                    if(stringNode->getItem()==subStringNode->getItem())
                    {   
                        count++;
                        cout << subStringNode->getItem() << endl;
                        subStringNode = subStringNode->getNext();
                        if(subStringNode==nullptr && count==lc.nodeCount)
                        {
                            return true;
                        }
                    }
                    stringNode = stringNode->getNext();
                }
            }
            return false;
        }

        void clear()
        {   
            Node *deleteNode;
            while(head!=nullptr) {
                Node *deleteNode = head;
                head = head->getNext();
                delete deleteNode;
                deleteNode = nullptr;
            }      
        }

};


int main()
{   
    
    int userChoice;
    LinkedChar someLinkedList;
    char userCharInput;
    string userInput;

    while(userChoice!=7)
    {   
        std::cout << "Enter a Choice:" << endl;
        std::cout << "1. Enter New String" << endl;
        std::cout << "2. Print the Linked Char List w/memory address" << endl; 
        std::cout << "3. Get Length of Linked List" << endl;
        std::cout << "4. Find Index of Character" << endl;
        std::cout << "5. Append New string/Linked List to existing Linked List: " << endl;
        std::cout << "6. Check if string is a submatch" << endl;
        std::cout << "7. Exit " << endl;
        std::cin >> userChoice;      
        
        switch(userChoice){
            case 1: 
                std::cout << "Enter a word(s) to create a Linked Character List: ";
                std::cin.ignore();
                getline(cin, userInput);
                someLinkedList = LinkedChar(userInput);
                std::cout << "You entered the word " << userInput << endl; 
                break;
            case 2:
                someLinkedList.printLinkedChar();
                break;
            case 3: 
                std::cout << "Current Length of Stored Linked Character List: " << someLinkedList.length() << endl;
                break;
            case 4:
                std::cout << "Enter the Character you would like the Index of: ";
                std::cin >> userCharInput;
                std::cout << "The index of char " << "'" << userCharInput << "'" << ": " << someLinkedList.index(userCharInput) << endl;
                break;
            case 5:
                std::cout << "Append New Linked Char List to Current Linked Char List: ";
                std::cin.ignore();
                getline(cin, userInput);
                someLinkedList.append(userInput);
                std::cout << endl;
                std::cout << "The Linked Char list is now: " << endl; 
                someLinkedList.printLinkedChar();
                std::cout << endl;
                break;        
            case 6:
                std::cout << "Check if Linked Char passed in is a submatch of existing Linked Char List" << endl;
                std::cout << "Enter a string: ";
                std::cin.ignore(); // Clear Buffer Stream
                getline(cin, userInput);
                LinkedChar someLinkedList2 = LinkedChar(userInput);
                cout << endl; 
                int match = someLinkedList.subStringMatch(someLinkedList2);
                if (match)
                {
                    cout << "Substring " << userInput << "? True" << endl;
                } else {
                     cout << "Substring " << userInput << "? False" << endl;
                }
                break;                  
        };
    };


    // string someString = "hello";
    // string someString2 = "world";
    // char someChar = 'l';
    // // Initialize Linked List and Pass in String
    // LinkedChar someChars = LinkedChar(someString); 
    // // std::cout << "Current Node count: " << someChars.length() << endl;
    // // Append Some Linked Char to Another
    // someChars.append(someString2);
    // // std::cout << "New Node count after append: " << someChars.length() << endl;
    // // Print LinkedChars
    // // someChars.printLinkedChar();
    // // std::cout << "Matching letter is index: " << someChars.index(someChar) << endl;
    
    // string someString3 = "farl";
    // LinkedChar someChars2 = LinkedChar(someString3);
    // cout << "Is a substring? " << someChars.submatch(someChars2) << endl;
    // // Get Index of a matching char in Linked List
    // // std::cout << "Clearing Memory: " << endl;
    // // someChars.clear();
    // // std::cout << "Done!" << endl;
    return 0;

}