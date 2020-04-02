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
        
        void displayList(){
            for (list<string>::iterator it = privateGifts.begin(); it != privateGifts.end(); ++it)
            {
                cout << (*it) << "\n";
            }
        };

        void addGift(string gift)
        {
            privateGifts.push_back(gift);
        };
        
};

int main()
{
    string child;
    string singleGift;
    bool namesComplete = false; 
    list<children> giftList; 
     
    while(!namesComplete){
        cout << "Name for nice list: ";
        getline(cin, child);

        if (child==""){
            namesComplete = true;
        }

        if(namesComplete == false)
        {
            list<string> singleChildList; 
            cout << "add gifts for " << child << endl;
            cout << "gift: ";
            getline(cin, singleGift);
            // Create Child and Gift List 
            children someChild;
            someChild.setName(child);
            someChild.setList(singleChildList);
            someChild.addGift(singleGift);

            bool giftListComplete = false;
            while(!giftListComplete){
                cout << "gift: ";
                getline(cin, singleGift);
                someChild.addGift(singleGift);
                if(singleGift=="")
                {
                    giftListComplete = true;
                }
            }
            giftList.push_back(someChild);
        }
    }
    
    // Print the List of Gifts Out
    for (std::list<children>::iterator it = giftList.begin(); it != giftList.end(); ++it)
    {
        children iter = *it;
        cout << iter.getName() << "'s gifts: " << endl;
        iter.displayList(); 
    }
    
    return 0;
}