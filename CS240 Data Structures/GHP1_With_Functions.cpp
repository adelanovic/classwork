/*
   Written by: Delanovic, Adis
   Date: 09/03/2019
   Class: CS240 Data Structures and Algorithms
   Instructor: Professor Sarner
   Compiler: CodeBlocks Version 17.12 in Windows Environment / set to use C++98 compiler

   Purpose of this program is to generate a matrix with random numbers based on the users input.
   The user then searches for a specific number in the matrix. The user is notified whether the number
   is found or not.
*/



#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//Function Prototypes. All listed in order they are called.

   int welcome();
   void createMatrix(int(*)[5], const int, const int, int);
   void printMatrix(const int(*)[5], const int, const int);
   int selectValue(int);
   void searchMatrix(const int(*)[5], const int, int, const int);
   void displayResult(bool, int);
   void windowStaysOpen();


int main(void)
{
    int matrixVal = 0;
    int searchVal = 0;
    const int row = 5;
    const int col = 5;
    bool flag = false;

//Static array initialized at 5x5 and all values set to 0.
    int matrix[5][5] = {0};

//Function calls.

    matrixVal = welcome();

    createMatrix(matrix, row, col, matrixVal);

    searchVal = selectValue(matrixVal);

    searchMatrix(matrix, row, col, searchVal);

    windowStaysOpen();

    return 0;
}


//Function definitions.

//Created by: Adis
//Date: 09/03/2019
//Welcomes the user to the program and asks them to enter the highest number they want possible
//to be generated in the 5x5 matrix. Also ensures that the user enters a positive non-zero
//integer otherwise it'll keep prompting. A return value is an integer.

//Pre-condition: A positive integer greater than zero.
//Post- Condition: Value is saved, returned and sent to another function.

int welcome()
{
    int enterVal = 0;

    cout << "This program generates a random matrix based on users input maximum value (inclusive).\n";
    cout << "You can then search for a value and see if it is located in the matrix.\n\n";
    cout << "\t\t\tPlease enter the highest value you want in your matrix greater than zero: ";
    cin >> enterVal;
    cout << "\n";

    while( enterVal <= 0 )
    {
        cout << "\t\t\tPlease enter a positive non-zero integer: ";
        cin >> enterVal;
    }

    return enterVal;


}

//Created by: Adis
//Date: 09/03/2019
//Using modulo and the user input value it creates a matrix of size 5x5.
//The number entered is inclusive and therefore the (rand() % n) + 1
//No return value, but the matrix is created and accessible by the main program since its argument is an array.
//Professor Christopher Urban used a similar method to fill out a 1D array in one of his homework assignments Spring 2019 CS108.
//Calls the printMatrix() function to display the matrix on the screen.

void createMatrix(int arr[][5], const int row, const int col, int n)
{
    srand((unsigned)time(NULL));

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            arr[i][j] = (rand() % n) + 1;
        }
    }

    printMatrix(arr, row, col);

    return;

}

//Created by: Adis
//Date: 09/03/2019
//Prints out a 2D array.
//No return type, accepts a 2D array as an argument and displays it on the screen.

void printMatrix(const int arr[][5], const int row, const int col)
{
    for(int i = 0; i < row; i++)
    {
        cout << "\t\t\t";

        for(int j = 0; j < col; j++)
            {
            cout  << arr[i][j] << "\t" ;
            }
        cout << "\n" ;
    }

    cout << "\n";

    return;
}

//Created by: Adis
//Date: 09/03/2019
//Prompts the user to enter a value they are searching for. Returns an integer to the main program.
//The loop will keep executing until the user enters a proper number that is within the range of
//the number they used to generate the matrix inclusive.

int selectValue(int n)
{
    int sVal = 0;

    cout << "\t\t\tPlease enter the value you are looking for: ";
    cin >> sVal;

    while(sVal > n || sVal <= 0)
    {
        cout << "\t\t\tPlease re-enter value equal to or smaller than your maximum value: ";
        cin >> sVal;
    }

    cout << " \n";

    return sVal;
}

//Created by: Adis
//Date: 09/03/2019
//Searches an array for a value that has been sent to it by the user. The array returns a boolean (true or false)
//based on if the value was found or not.
//the j = col, and i = row are used to immediately force the for loop to meet the conditions to terminate itself.
//Calls the displayResults() function to display if the value was found or not.

//Pre-Condition: A 2D array is searched for a value.
//Post-Condition: Flag stays false if the value isn't found. The entire array is searched, or turns into true if the value is found. The loop is then
//                forced to meet its condition and terminate early.

void searchMatrix(const int arr[][5], const int row, const int col, int n)
{
    bool flag = false;

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(arr[i][j] == n)
            {
                    flag = true;
                    displayResult(flag, n);
                    return;
            }
        }
    }

displayResult(flag, n);

return;
}

//Created by: Adis
//Date: 09/03/2019
//Displays the results based on what the searchMatrix() function returned the bool flag as either true or false.
//Takes a bool as argument, and an int is passed so that i can display what the user originally entered.

void displayResult(bool n, int m)
{
    if(n == true)
    {
        cout << "\t\t\tYour entered value " << m << " was found \n";
    }
    else
    {
        cout << "\t\t\tYour value " << m << " was not found \n";
    }

    return;
}

//Created by: Bjarne Stroustrup
//Book Title and Page: Programming Principles and Practice Using C++, pg53
//First time using an IDE and my prompt kept exiting after running. I needed a way to keep the window open.
//The cin stream is created just to keep the window from closing.

void windowStaysOpen()
{
    cout << "\n\t\t\tType any character and press enter to exit. ";
    char ex;
    cin >> ex;

    return;
}



