// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include <iostream>
#include <string>
#include "LinkedStack.h"

void stackTester(StackInterface<std::string>* stackPtr)
{
	try
   {
      std::string items[] = {"zero", "one", "two", "three", "four", "five"};
      std::cout << "Empty: " << stackPtr->isEmpty() << std::endl;
      for (int i = 0; i < 6; i++)
      {
         std::cout<<"Pushing " << items[i] << std::endl;
         bool success = stackPtr->push(items[i]);
         if (!success)
            std::cout << "Failed to push " << items[i] << " onto the stack." << std::endl;
      }
      
      std::cout << "Empty?: " << stackPtr->isEmpty() << std::endl;
      
      for (int i = 0; i < 6; i++)
      {
         std::cout << "Loop " << i << std::endl;
         std::cout << "peek1: " << stackPtr->peek() << std::endl;
         std::cout << "pop: " << stackPtr->pop() << std::endl;
         std::cout << "Empty: " << stackPtr->isEmpty() << std::endl;
      }
      std::cout << "Empty: " << stackPtr->isEmpty() << std::endl;
      std::cout << "pop an empty stack: " << std::endl;
      std::cout << "pop: " << stackPtr->pop() << std::endl;   // nothing to pop!

      std::cout << "peek into an empty stack: " << std::endl;
      std::cout << "peek: " << stackPtr->peek() << std::endl; // nothing to peek!
   }
   catch (PrecondViolatedExcep e)
   {
      std::cout << e.what();
   }  // end try/catch
}  // end stackTester

int main()
{
	StackInterface<std::string>* stackPtr = new LinkedStack<std::string>();
	std::cout << "Testing the Link-Based Stack:" << std::endl;
	stackTester(stackPtr);
	
   return 0;
}  // end main

/*
 Testing the Link-Based Stack:
 Empty: 1
 Pushing zero
 Pushing one
 Pushing two
 Pushing three
 Pushing four
 Pushing five
 Empty?: 0
 Loop 0
 peek1: five
 pop: 1
 Empty: 0
 Loop 1
 peek1: four
 pop: 1
 Empty: 0
 Loop 2
 peek1: three
 pop: 1
 Empty: 0
 Loop 3
 peek1: two
 pop: 1
 Empty: 0
 Loop 4
 peek1: one
 pop: 1
 Empty: 0
 Loop 5
 peek1: zero
 pop: 1
 Empty: 1
 Empty: 1
 pop an empty stack:
 pop: 0
 peek into an empty stack:
 peek: Precondition Violated Exception: peek() called with empty stack.
*/
