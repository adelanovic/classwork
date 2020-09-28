/*
    By: Delanovic Adis
    Date: 09/30/2019
    Assignment: GHP #3, Find total words, and total words that begin with letter d.
    Class: CS240 Data Structures and Algorithms
    Instructor: Professor Sarner
    Compiler: Code::Blocks v.17.12 IDE for Windows set to C++98 compiler.

    Description of Program: This program opens a file. The file is then traversed from start to end. All
        the words are counted. All the words that begin with 'D' or 'd' are also counted separately.
        The main problem here would be how to go through all the words (how do i know that I'm at a new word?
        HINT: blank spaces processing with ifstream and '\0'),
        and how to figure out at what point am i at the start of a new word (HINT: word[0]).

        Also if a word is in "quotes" how can i ensure the 'd' or 'D' is counted as well.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cctype>

using namespace std;

//Function prototypes.
void findWords(ifstream &);
void printResults(const int, const int);

int main(void)
{
    //Variable of class type ifstream, <fstream> library.
    //I need string data type with ifstream data type in conjunction to create
    //the file stream.
    string filename;
    ifstream readFile;

    //Prompt user to enter a file.
    cout << "Enter File Name: ";
    getline(cin, filename);

    //Open the file stream.
    readFile.open(filename.data());

    //Assertion to check if it opened correctly. I can use a while(!readFile) to continue
    //prompting the user.
    assert(readFile.is_open());

    //Function call to find total words.
    findWords(readFile);

    //Close the file stream.
    readFile.close();

return 0;
}

//Name: Adis
//Date: 09/30/2019
//Pre-Condition: The function takes a input file stream as an argument.
//Post-Condition: The file stream is traversed from start to finish. The number of words are counted in
//                the file. The number of words that begin with 'D' are counted irrespective of case.
//                The printResults() function is called and displays the count totals.
//                cctype function tolower() is used to find 'd' irrespective of case.
//                string function isalpha() is used to check for quotes.
void findWords(ifstream &inputFile)
{
    string word;
    int dCount = 0;
    int wCount = 0;
    while(!inputFile.eof())
    {
        while( inputFile >> word)
        {
            wCount++;

            //Finding 'D' or 'd'
            if((tolower(word[0]) == 'd') || (!isalpha(word[0]) && tolower(word[1]) == 'd'))
            {
                dCount++;
            }
        }
    }

    //Function call to print total counts for both D's and words.
    printResults(wCount, dCount);

    return;
}

//Name: Adis
//Date: 09/30/2019
//Pre-condition: Given two constant integers.
//Post-Condition: The integers are displayed on the screen.
void printResults(const int wCount, const int dCount)
{
    cout << "There are " << wCount << " words total in this file. " << endl;
    cout << "There are " << dCount << " words that begin with the letter 'D' irrespective of case." << endl;

    return;
}
