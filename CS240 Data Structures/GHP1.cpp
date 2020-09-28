/*
   Written by: Delanovic, Adis
   Date: 08/27/2019
   Class: CS240 Data Structures and Algorithms
   Instructor: Professor Sarner
   Compiler: CodeBlocks Version 17.12 in Windows Environment / set to use C++98 compiler

   Purpose of this program is to generate a matrix with random numbers based on the users input.
   The user then searches for a specific number in the matrix. The user is notified whether the number
   is found or not.

*/



#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*
   Used to keep the window open when running executable.
   Function prototype, void return type no parameter.
   Got the idea from (Programming: Principles & Practice Using C++ Stroustrup, Pg )
*/
   void windowStaysOpen();

int main(void)
{
    //Declare and initialized variables, the matrix is initialized to have a value of 0 for the entire table.
    int userVal = 0;
    int searchVal = 0;
    int matrix[5][5] = {0};
    int row = 5;
    int col = 5;
    bool flag = false;

    //Needed so that i can use the rand() function to fill the matrix
    srand((unsigned)time(NULL));


    //Tell the user what the program does, prompts them to enter a value and stores that value in memory.
    cout << "This program generates a random matrix based on users input maximum value.\n";
    cout << "You can then search for a value and see if it is located in the matrix.\n\n";
    cout << "\t\t\tPlease enter the highest value you want in your matrix: ";
    cin >> userVal;

    //Ensuring that the user enters a positive non-zero integer
    while( userVal <= 0 )
    {
        cout << "\t\t\tPlease enter a positive non-zero integer: ";
        cin >> userVal;
    }


    //Using the rand() function with conjunction of modulo to fill out the matrix rows and columns.
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            matrix[i][j] = (rand() % userVal) + 1;
        }
    }

    //Prints out the matrix, properly formatted to have a clear picture of the rows/columns.
    for(int i = 0; i < row; i++)
    {
        cout << "\t\t\t";
        for(int j = 0; j < col; j++)
        {
            cout  << matrix[i][j] << "\t" ;
        }
        cout << "\n" ;
    }

    cout << "\n\n";

    //Prompt user for what value they are looking for
    cout << "\t\t\tPlease enter the value you are looking for: ";
    cin >> searchVal;

    //Ensuring that the user enters a proper search value that has a possibility to be in the randomly generated matrix
    while(searchVal > userVal)
    {
        cout << "\t\t\tPlease re-enter value equal to or larger than your maximum value: \n";
        cin >> searchVal;
    }

    cout << " \n\n";

    //Searches through the matrix to see if the value the user is looking for is present.
    //Since i can't use the break; command i preferred to just keep count of how many times the value was found.
    for(int i = 0; i < col; i++)
    {
        for(int j = 0; j < row; j++)
        {
            if(matrix[i][j] == searchVal)
            {
                    flag = true;
                    j = 5;
                    i = 5;
            }

        }
    }



    //Prints results based on if the value the user is searching for is found or not.
    if(flag == true)
    {
        cout << "\nYour entered value " << searchVal << " was found \n";
    }
    else
    {
        cout << "Your value " << searchVal << " was not found \n";
    }

    //Function Call, preventing the executable from closing when run standalone outside of IDE
    windowStaysOpen();

    return 0;
}

//Function definition
void windowStaysOpen()
{
    cout << "\nType any character and press enter to exit: ";
    char ex;
    cin >> ex;

}

/* References: */

