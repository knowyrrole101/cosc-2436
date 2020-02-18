//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <iostream>
#include <string>
#include "ArrayBag.h"

void displayBag(ArrayBag<std::string>& bag)
{
   std::cout << "The bag contains " << bag.getCurrentSize()
        << " items:" << std::endl;
   std::vector<std::string> bagItems = bag.toVector();
   int numberOfEntries = (int)bagItems.size();
   for (int i = 0; i < numberOfEntries; i++)
   {
      std::cout << bagItems[i] << " ";
   }  // end for
   std::cout << std::endl << std::endl;
}  // end displayBag

void bagTester(ArrayBag<std::string>& bag)
{
   std::cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 1 (true)" << std::endl;
   displayBag(bag);
   
   std::string items[] = {"one", "two", "three", "four", "five", "one"};
   std::cout << "Add 6 items to the bag: " << std::endl;
   for (int i = 0; i < 6; i++)
   {
      bag.add(items[i]);
   }  // end for
   
   displayBag(bag);
   
   std::cout << "isEmpty: returns " << bag.isEmpty()
        << "; should be 0 (false)" << std::endl;
   
   std::cout << "getCurrentSize: returns " << bag.getCurrentSize()
        << "; should be 6" << std::endl;
   
   std::cout << "Try to add another entry: add(\"extra\") returns "
        << bag.add("extra") << std::endl;
} // end bagTester

int main()
{
   ArrayBag<std::string> bag;
   std::cout << "Testing the Array-Based Bag:" << std::endl;
   std::cout << "The initial bag is empty." << std::endl;
   bagTester(bag);
   std::cout << "All done!" << std::endl;
   
   return 0;
} // end main

/*
 Testing the Array-Based Bag:
 The initial bag is empty.
 isEmpty: returns 1; should be 1 (true)
 The bag contains 0 items:
 
 
 Add 6 items to the bag:
 The bag contains 6 items:
 one two three four five one
 
 isEmpty: returns 0; should be 0 (false)
 getCurrentSize: returns 6; should be 6
 Try to add another entry: add("extra") returns 0
 All done!
*/
