#include "children.h"
#include <iostream>
#include <list>

using namespace std;

// Constructor Method
children::children(string name, list<string>gifts)
{   
    cout << name << endl;
    setName(name);
    setList(gifts);
}

// Set childs name in private attribute
void children::setName(string name){
        privateName = name;
}

// Set childs list to private and store in private attribute
void children::setList(list<string> gifts){
        privateGifts = gifts;
}

// Display List of Gifts
void children::displayList(){      
        for (list<string>::iterator it = privateGifts.begin(); it != privateGifts.end(); ++it)
        {
            cout << (*it) << " ";
        }
    }

// Add a gift to the existing child list of gifts
void children::addGift(string gift){ 
    cout << "Adding gift" << endl;
        // privateGifts.push_back(gift);
}

// Get list of Gifts for Child
list<string> children::getGifts(){
        return privateGifts;
}

// Get String of Child Name
string children::getName(){
        return privateName;
}
