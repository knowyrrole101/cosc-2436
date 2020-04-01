/*
    MAMUN AHMED
    COSC 2436 - T/TH - LAB 4

    Get user input of childs name, and gifts in while loop
    Pass name and list of gifts to Children Object
    Push each gift to back of list.
    Print the list of names and gifts for each child
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <list>

using namespace std;

class children
{   
    private:
        string privateName;
        list<string> privateGifts;

    public:
        children(){};
        void setName(string name)
        {
            privateName = name;
        };
        void setList(list<string> gifts)
        {   
            privateGifts = gifts;
        };
        string getName(){
            return privateName;
        };
        list<string> getGifts(){
            return privateGifts;
        };
        void displayList();
        void addGift(string gift)
        {
            privateGifts.push_back(gift);
        };
        
};



int main()
{
    string child;
    string singleGift;
    list<children> giftList; //the list of objects

    cout << "Name for nice list: ";
    getline(cin, child);

    while(child!=""){
        list<string> listOfGifts; 
        
        cout << "add gifts for " << child << endl;
        cout << "gift: ";
        
        getline(cin, singleGift);
        // Create Child and Gift List and Add First Gift
        children someChild;
        someChild.setName(child);
        someChild.setList(listOfGifts);
        someChild.addGift(singleGift);
        
        while(singleGift!=""){
            cout << "gift: ";
            getline(cin, singleGift);
            someChild.addGift(singleGift);
        }

        // giftList.push_back(theChild); //adds the item to the list of the kids with objects

        // cout << "Name for nice list: ";
        // getline(cin, child);
    }

    // cout << "The list contains";
    // for (list<children>::iterator it = giftList.begin(); it != giftList.end(); ++it)
    //     {
    //         children child = *it;
    //         cout << "\n" << child.getName() << " ";
    //         child.displayList();
    //     }

    return 0;
}