/*
   By: Delanovic Adis
   Date: 09/25/2019
   Assignment: GHP #3
   Class: CS240 Data Structures and Algorithms
   Instructor: Professor Sarner

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void findWords(int &count1, int &count2, int &count3, int &count4);
void printResults(const int count1, const int count2, const int count3,const int count4);

int main(void)
{
   int wordCount = 0;
   int deesCount = 0;
   int charCount = 0;
   int vowels = 0;

   findWords(wordCount, deesCount, charCount, vowels);
   printResults(wordCount, deesCount, charCount, vowels);

   return 0;
}


void findWords(int &wordCount, int &deesCount, int &charCount, int &vowels)
{
    string words;
    string filename;

    ifstream readFile;
    cout << "Enter File Name: ";
    getline(cin, filename);

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
            return;
        }
        else
        {
            readFile.open(filename.c_str());
        }

    }

    //Reads a file until reaching the end of file marker.
    //Counts words
    //Counts D's or d's
    //Counts vowels
    while(!readFile.eof())
    {
        while( readFile >> words)
        {
            wordCount++;
            if(words[0] == 'd' || words[0] == 'D' )
            {
                deesCount++;
            }
            if(words[1] == '\0')
            {
                charCount++;
            }
            for(int i = 0; i < sizeof(words); i++)
            {
                if((words[i] == 'a') || (words[i] == 'e') || (words[i] == 'i') || (words[i] == 'o') || (words[i] == 'u'))
                {
                    vowels++;
                }
            }

        }
    }

    readFile.close();
    return;
}

void printResults(const int wordCount, const int deesCount,const int charCount,const int vowels)
{
    cout << "There are " << wordCount << " words. This is including " << charCount << " characters by themselves." << endl;
    cout << "There are " << deesCount << " words that begin with the letter D." << endl;
    cout << "There are " << vowels << " vowels in our file." << endl;

    return;
}
