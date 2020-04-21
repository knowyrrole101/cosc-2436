// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include "ArrayList.h" // ADT list operations
#include <iostream>
#include <string>

void displayList(ListInterface<std::string>* listPtr)
{
	std::cout << "The list contains " << std::endl;
   for (int pos = 1; pos <= listPtr->getLength(); pos++)
   {
      try
      {
         std::cout << listPtr->getEntry(pos) << " ";
      }
      catch(PrecondViolatedExcep except)
      {
         std::cout << "Exception thrown getting entry inserted at position " << pos << std::endl;
         std::cout << except.what() << std::endl;
      }
    } // end for
	std::cout << std::endl;
}  // end displayList

void listTester(ListInterface<std::string>* listPtr)
{
   std::string data[] = {"one", "two", "three", "four", "five", "six"};
   std::cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 1 (true)" << std::endl;
   for (int i = 0; i < 6; i++)
   {
      if (listPtr->insert(i + 1, data[i]))
      {
         try
         {
            std::cout << "Inserted " << listPtr->getEntry(i + 1) << " at position " << (i + 1) << std::endl;
         } catch (PrecondViolatedExcep except)
         {
            std::cout << "Exception thrown getting entry inserted at list end!" << std::endl;
            std::cout << except.what() << std::endl;
         }
      }
      else
         std::cout << "Cannot insert " << data[i] << " at position " << (i + 1) << std::endl;
   }  // end for
   
   displayList(listPtr);
   
   std::cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 0 (false)" << std::endl;
   std::cout << "getLength returns : " << listPtr->getLength() << "; should be 5" << std::endl;
   
   try
   {
      std::cout << "The entry at position 4 is " << listPtr->getEntry(4) << "; should be four" << std::endl;
   }
   catch (PrecondViolatedExcep except)
   {
      std::cout << "Exception thrown getting entry at position 4!" << std::endl;
      std::cout << except.what() << std::endl;
   }
   std::cout << "After replacing the entry at position 3 with XXX: ";
   try
   {
      listPtr->replace(3, "XXX");
   }
   catch (PrecondViolatedExcep except)
   {
      std::cout << "Exception thrown getting entry at position 3!" << std::endl;
      std::cout << except.what() << std::endl;
   }
   displayList(listPtr);
   
   std::cout << "remove(2): returns " << listPtr->remove(2) << "; should be 1 (true)" << std::endl;
   std::cout << "remove(1): returns " << listPtr->remove(1) << "; should be 1 (true)" << std::endl;
   std::cout << "remove(6): returns " << listPtr->remove(6) << "; should be 0 (false)" << std::endl;
   displayList(listPtr);
   
   std::cout << "clear: " << std::endl;
   listPtr->clear();
   std::cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 1 (true)" << std::endl;
   
   try
   {
      std::cout << "Attempt an illegal retrieval from position 6: " << std::endl;
      listPtr->getEntry(6);
   }
   catch(PrecondViolatedExcep e)
   {
      std::cout << e.what() << std::endl;
   }  // end try/catch
   
   try
   {
      std::cout << "Attempt an illegal replacement at position 6: " << std::endl;
      listPtr->replace(6, "YYY");
   }
   catch(PrecondViolatedExcep e)
   {
      std::cout << e.what() << std::endl;
   }  // end try/catch
   
} // end listTester

int main()
{
	ListInterface<std::string>* listPtr = new ArrayList<std::string>();
	std::cout << "Testing the Array-Based List:" << std::endl;
	listTester(listPtr);
   return 0;
}  // end main

/*
 Testing the Array-Based List:
 isEmpty: returns 1; should be 1 (true)
 Inserted one at position 1
 Inserted two at position 2
 Inserted three at position 3
 Inserted four at position 4
 Inserted five at position 5
 Cannot insert six at position 6
 The list contains 
 one two three four five 
 isEmpty: returns 0; should be 0 (false)
 getLength returns : 5; should be 5
 The entry at position 4 is four; should be four
 After replacing the entry at position 3 with XXX: The list contains 
 one two XXX four five 
 remove(2): returns 1; should be 1 (true)
 remove(1): returns 1; should be 1 (true)
 remove(6): returns 0; should be 0 (false)
 The list contains 
 XXX four five 
 clear: 
 isEmpty: returns 1; should be 1 (true)
 Attempt an illegal retrieval from position 6: 
 Precondition Violated Exception: getEntry() called with an empty list or invalid position.
 Attempt an illegal replacement at position 6: 
 Precondition Violated Exception: replace() called with an invalid position. 
*/
