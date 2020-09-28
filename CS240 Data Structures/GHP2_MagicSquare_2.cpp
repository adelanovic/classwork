/*

  Name: Adis Delanovic
  Assignment: Graded Homework #2, Magic Square, pg139 Problem #9.
  Instructor: Professor Sarner
  Description of Program: Given an odd n square of rows/cols generate a square where all the rows, columns add up to the same number.
                          Both rows and columns have to be the same odd integer.

*/

#include <iostream>
#define ROW 51
#define COL 51

using namespace std;

int enterValue();
void createMagic(int a[][COL], const int, const int, const int);
void printMagic(const int a[][COL], int, int);
void addMagic(const int a[][COL], int b[],int c[], int, int, int);


int main(void)
{

    int magic[ROW][COL] = {0};
    int addRows[ROW] = {0};
    int addCols[COL] = {0};
    int addDiag = 0;
    int userVal = 0;

    cout << "\t\t\tGet ready to create MAGIC!" << "\n\n";

    //Determining the starting point for our array.
    userVal = enterValue();
    int middle = int(userVal/2);

    //Function calls to create matrix, print it, and ensure they all add up to the same value.
    createMagic(magic, userVal, userVal, middle);
    addMagic(magic, addRows, addCols, addDiag, userVal, userVal);



return 0;
}

/*
   Created by: Adis
   Date: 09/15/2019
   Description: Returns an odd integer to the calling environment. Using conditions ensures that the value isn't even, greater than
   the array ([51][51] in this case), or equal to or less than 1.

   Pre-Condition: User enters an unsigned odd integer greater than 1, but less than or equal to the static array allocation.
   Post-Condition: The odd integer is returned to the calling environment.
*/
int enterValue()
{
    int val = 0;

    cout << "\t\t\tPlease enter an odd integer greater than 1 but less or equal to 51: ";
    cin >> val;
    cout << "\n";

    while((val % 2 == 0) || (val > 51) || (val <= 1))
    {
        cout << "\t\t\tPlease re-enter a proper odd integer greater than 1 but less or equal to 51: ";
        cin >> val;
        cout << "\n";
    }

    return val;

}



/*
   Created by: Adis
   Date: 09/15/2019
   Description: In order to create a Magic Square the square is filled in a specific manner. There are conditions that exist that
                tell you which place to go next.

   Pre-Condition: Given an odd array of equal number columns and rows.
   Post-Condition: The array is traversed and filled in such a way where all the columns, rows, and diagonally add up to the same number.
*/
void createMagic(int arr[][COL],int col, int row, int start)
{
    //Setting up my starting point outside of the loop.
    int i = 0;
    int j = start;
    int k = 1;
    arr[0][start] = k;


    //Adding k + 1 into my matrix until k = col * row. These conditions were explained on Pg139 Nyhoff.
    do
    {
        i--;
        j++;
        k++;

        if(i < 0 && j < col)
        {
            i = row - 1;
            arr[i][j] = k;
        }

        else if( j >= col && i >= 0)
        {
            j = 0;
            arr[i][j] = k;
        }

        else if( ((i < 0) && (j >= col)) || arr[i][j] > 0)
        {
            i = i + 2;
            j = j - 1;
            arr[i][j] = k;
        }

        else
        {
            arr[i][j] = k;
        }


    } while ( k != (row * col));

    printMagic(arr, row, col);

return;

}

/*
   Created by: Adis
   Date: 9/25/2019
   Description: Prints an array, staying within the bounds of the odd user value entered.
*/
void printMagic(const int arr[][COL], int row, int col)
{

for( int i = 0; i < row; i ++)
    {
    cout << "\t\t\t";

    for( int j = 0; j < col; j++)
        {
        cout << arr[i][j] << "\t";
        }

    cout << "\n";
    }
}

/*
  Created by: Adis
  Date: 9/15/2019
  Description: Adds up an all the rows, all the columns, and rows/columns diagonally. It then prints them out. If our
               Magic Square solution is correct all the numbers will be the same.
*/
void addMagic(const int arr[][COL], int addRows[], int addCols[], int addDiag, int row, int col)
{
    int i = 0;
    int j = 0;

    cout << "\n\t\t\tYour MAGIC number is......" <<endl;

    //Add and print rows.
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            addRows[i] += arr[i][j];
        }

    }
    cout << "\n";
    cout << "\t\t\tAll the rows added up:\t  ";

    for(i = 0; i < row; i++)
    {
      cout << addRows[i] << " ";
    }

    //Add and print columns.
    for(i = 0; i < col; i++)
    {
      for(j = 0; j < row; j++)
      {
        addCols[i] += arr[j][i];
      }
    }
    cout << "\n";
    cout << "\t\t\tAll the columns added up: ";

    for(i = 0; i < row; i++)
    {
      cout << addCols[i] << " ";
    }

    //Add and print diagonally.
    i = 0;
    j = 0;
    while( i < row)
    {
        addDiag += arr[i][j];
        i++;
        j++;
    }

    cout << "\n\t\t\tAdded up diagonally:\t  " << addDiag << endl;


return;
}
