#ifndef CHILDREN_H
#define CHILDREN_H
#include <string>
#include <list>

using namespace std;

class children
{   
    private:
        string privateName;
        list<string> privateGifts;

    public:
        children(string name, list<string>gifts){}
        void setName(string name);
        void setList(list<string> gifts);
        string getName();
        list<string> getGifts();
        void displayList();
        void addGift(string gift);
};

#endif 