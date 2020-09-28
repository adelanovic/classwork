
/*
    Written by: Delanovic, Adis

    Pre-condition: 2

    Post-condition:


*/

//Function Prototypes

#include <iostream>
#define ROW 51
#define COL 51

using namespace std;

void addMagic(const int a[][COL], int b[],int c[], int, int, int);

int main(void)
{

int userVal = 0;
int magic[ROW][COL] = {0};
int addRows[ROW] = {0};
int addCols[COL] = {0};
int addDiag = 0;


cout << "Please enter an odd integer greater than 1 but equal or less than 51: ";
cin >> userVal;
int middle = int(userVal/2);
const int row = userVal;
const int col = userVal;
int magicAdd[row * 2] = {0};

//Creating a starting point for our magic square
int k = 1;
int i = 0;
int j = middle;

magic[0][middle] = k;


do
{
    i--;
    j++;
    k++;

    if(i < 0 && j < col)
    {
        i = row - 1;
        magic[i][j] = k;
    }

    else if( j >= col && i >= 0)
    {
        j = 0;
        magic[i][j] = k;
    }

    else if( ((i < 0) && (j >= col)) || magic[i][j] > 0)
    {
        i = i + 2;
        j = j - 1;
        magic[i][j] = k;
    }


    else
    {
        magic[i][j] = k;
    }


}while ( k != (row * col));



// Print our magic square
for( i = 0; i < row; i ++)
    {
    for(j = 0; j < col; j++)
        {
        cout << magic[i][j] << "\t";
        }

    cout << "\n";
}

addMagic(magic, addRows, addCols, addDiag, row, col);
//Testing to ensure the numbers match



return 0;
}


/*Created by: Adis
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
