/*
    MAMUN AHMED
    COSC 2436 - T/TH - LAB 1 
    LAB 1 - MAXARRAY RECURSIVE FUNCTION
    Output: Program should take in a array with ElementType
    and return the max from the array
*/
#include <iostream>
#include <string>

using namespace std;

// Function Template 
template<class ElementType>
ElementType maxArray(ElementType someArray[], int firstIndex, int lastIndex); 

// Main Function
int main()
{   
    // Test Int Array Max
    int intArray[] = {1, 5, 3, 4};
    int intMax = maxArray(intArray, 0, 3);
    cout << "Max integer in array is: " << intMax << endl;

    // Test Float Array Max
    float floatArray[] = {2.2, 5.5, 7.7, 1.2};
    float floatMax = maxArray(floatArray, 0, 3);
    cout << "Max float in array is: " << floatMax << endl;
}

template<class ElementType>
ElementType maxArray(ElementType someArray[], int firstIndex, int lastIndex)
{
    if(firstIndex == lastIndex) // Base Case
    {   
        return someArray[lastIndex];
    } 
    else 
    {   
        // Divid and Conquer - Array midpoint
        int mid = firstIndex + (lastIndex - firstIndex) / 2; 
        
        // Recursive calls for Left Maxes and Right Maxes
        ElementType leftMax = maxArray(someArray, firstIndex, mid);
        ElementType rightMax = maxArray(someArray, mid+1, lastIndex);
        return (leftMax > rightMax ? leftMax:rightMax);

    }
}