/*
    MAMUN AHMED

    COSC 2436 - T/TH - LAB 5
	
	SortedList CPP imports LinkedSortList Class Object
    that accepts INT type. 21 Random NUmbers are created
	and inserted into the LinkedList and sorted as they 
	are inserted.

	Last Value is removed and then output is displayed to
	end user.
*/
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "LinkedSortedList.h"


int main()
{
    srand((unsigned)time(0));
	LinkedSortedList<int> RanNumList;

	for (int i = 0; i < 21; i++)
	{
		RanNumList.insertSorted(rand() % 100 + 1);
	}

	RanNumList.remove(RanNumList.getLength());

	std::cout << "Sorted list: \n" << std::endl;

	for (int i = 1; i <= RanNumList.getLength(); i++)
	{
		std::cout << i << ":  " << RanNumList.getEntry(i) << std::endl;
	}

		return 0;
}
