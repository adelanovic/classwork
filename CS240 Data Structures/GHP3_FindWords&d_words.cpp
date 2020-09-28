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
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Function prototypes.
int findWords(ifstream &);
int findDees(ifstream &);
void printResults(const int, const int);

int main(void)
{
    int wordCount = 0;
    int dCount = 0;
    string filename;
    ifstream readFile;

    //Prompt user to enter a file.
    cout << "Enter File Name: ";
    getline(cin, filename);

    //Open the file stream.
    readFile.open(filename.c_str());

    //If the file fails to open. Keep prompting user until they decide they want to exit the program.
    while(!readFile)
    {
        cout << "Error opening file. " <<endl;
        cout << "Please re-enter file name or type -1 to exit: " << endl;
        getline(cin, filename);
        if(filename == "-1")
        {
            cout << "Exiting Program" << endl;
            return 0;
        }
        else
        {
            readFile.open(filename.c_str());
        }

    }
    //Function call to find total words and return an integer.
    wordCount = findWords(readFile);

    //Function call to find total D's irrespective of case and return an integer.
    dCount = findDees(readFile);

    //Function call to print total counts for both D's and words.
    printResults(wordCount, dCount);

    //Close the file stream.
    readFile.close();

return 0;
}

//Name: Adis
//Date: 09/30/2019
//Pre-Condition: The function takes a input file stream as an argument.
//Post-Condition: The file stream is traversed from start to finish. The number of words are counted in
//                the file. The number of words is incremented and returned to main. The file is then "rewound"
//                using
int findWords(ifstream &inputFile)
{

    string word;
    int wordsFound = 0;
    while(!inputFile.eof())
    {
        while( inputFile >> word)
        {
            wordsFound++;
        }
    }

    //Reset the file so we can pass through it again with another function. First we clear the stream using clear(). Then we use the
    //seekg() function to bring the file back to position 0 to start over if needed again. Using tellg() we can find the
    //current position start is at 0 and EOF is -1. I didn't want to pass by reference and do it all with one function.
    //EX: Using int position = inputFile.tellg(); and cout >> position; will give us our position in the file.
    inputFile.clear();
    inputFile.seekg(0);

return wordsFound;
}

//Name: Adis
//Date: 09/30/2019
//Pre-Condition: The function takes a input file stream as an argument.
//Post-Condition: The file stream is traversed from start to finish. The number of words that
//                begin with 'd' or 'D' are counted in the file (irrespective of case). The number
//                of words that begin with 'd' or 'D' is incremented and returned to main.
int findDees(ifstream &inputFile)
{
    string word;
    int dfound = 0;
    while(!inputFile.eof())
    {
        while( inputFile >> word)
        {
            if((word[0] == 'd') || (word[0] == 'D'))
            {
                dfound++;
            }

            //Making sure i found the d words that are quoted as well.
            //Could have put all this in the first if statement but easier read if separated.
            else if((word[0] == '"') && (word[1] == 'd' || word[1] == 'D'))
                dfound++;
        }
    }

    //Clearing stream again and setting it to start of file. (Explained in findWords()
    inputFile.clear();
    inputFile.seekg(0);

return dfound;
}

//Name: Adis
//Date: 09/30/2019
//Pre-condition: Given two constant integers.
//Post-Condition: The integers are displayed on the screen.
void printResults(const int w, const int d)
{
    cout << "There are " << w << " words total in this file. " << endl;
    cout << "There are " << d << " words that begin with the letter 'D' irrespective of case." << endl;

    return;
}
