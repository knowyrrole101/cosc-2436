/*
    MAMUN AHMED
    COSC 2436 - T/TH - LAB 3 
    Create a stack data structure using STL library
    then pass into a postfix calculator. The main function
    will accept a valid postfix expression and return a result
    Output: 
    
*/

#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Pass Stack Object to postfix expression calculator
stack<int> postfixCalculator(string &expression);
int charToInt(char &expression);
char intToChar(int &num);
void printStack(stack<int> s);

int main()
{   
    // Grab PostFix User Input 
    string userInput;
    std::cout << "Enter a postfix expession" << endl;
    cin >> userInput;
    // Run Postfix Calculator 
    stack<int> someTestStack = postfixCalculator(userInput);
    cout << "\n";
    cout << "The result for postfix expression is: " << someTestStack.top() << endl;
    
    return 0;
};

// PostFix Calculator Function
stack<int> postfixCalculator(string &expression){
    stack <int> someStack;
    for(int i=0; i<expression.length(); i++)
    {   
        // Valid Conversion of Char to Int 
        int num = charToInt(expression[i]);
        if(num>=0 && num<=9){
            cout << num << endl;
            someStack.push(num);
        } else {
            if(expression[i]=='+')
            {   
                int operand2 = someStack.top(); someStack.pop();
                int operand1 = someStack.top(); someStack.pop();
                int result = operand1 + operand2;
                someStack.push(result);
            } else if (expression[i]=='-'){               
                int operand2 = someStack.top(); someStack.pop();
                int operand1 = someStack.top(); someStack.pop();
                int result = operand1 - operand2;
                someStack.push(result);
            } else if (expression[i]=='*'){               
                int operand2 = someStack.top(); someStack.pop();
                int operand1 = someStack.top(); someStack.pop();
                int result = operand1 * operand2;
                someStack.push(result);
            } else if (expression[i]=='/'){               
                int operand2 = someStack.top(); someStack.pop();
                int operand1 = someStack.top(); someStack.pop();
                int result = operand1 / operand2;
                someStack.push(result);
            } 
        }
    }
    return someStack;
}

// Function to convert a char to int
int charToInt(char &expression)
{
    return (int)expression - '0';
}

// Function to print a stack
void printStack(stack<int> s) 
{ 
    if (s.empty()){
        return;
    }  
    int x = s.top(); 
    s.pop(); 
    printStack(s); 
    cout << x << " "; 
    // Push the same element onto the stack 
    // to preserve the order 
    s.push(x); 
} 
