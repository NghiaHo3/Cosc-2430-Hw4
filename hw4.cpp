//Nghia Ho
//ID 1251576
//Hw4
#include <iostream>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
#include "myTreeType.h"
//Check myTreeType header for all AVL tree functions
////////////////////////////////////////////////////////////////////////////////////////////
bool checkNumber(string userWord);
//Function that will check if userWord contain a number
bool checkPunct(string &userWord);
//Function that will check if userWord contain specific punctuation
//Function will also erase specific punctuation at the beginning and end of the userWord
string eraseWS(string &userWord);
//Function that will erase any unnecessary whitespace

////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;
int main(int argc, char* argv[])
{
    //ifstream ifs("12.txt");
    //ofstream ofs("out.txt");

////////////////////////////////////////////////////////////////////////////////////////////////////////
      if(argc<2)
      {
          cout<<"Usage: tree_sort \"A=<file>;C=<file>\""<<endl;
      }
      ArgumentManager am(argc, argv);
      //initializing input and output stream variable with their correspond file call
      ifstream ifs((am.get("A")).c_str());
      ofstream ofs((am.get("C")).c_str());
////////////////////////////////////////////////////////////////////////////////////////////////////////
    string word;
    //Initializing word variable
    myTreeType<string> wordTree;
    //Initializing wordTree object

        while(ifs>>word)
        {
            //Loop that will process every single word in the file
            eraseWS(word);
            //Erasing unnecessary whitespace before we begin
            if(!checkNumber(word)&&!checkPunct(word))
            //Checking for punctuation and number in word
            {
                wordTree.insert(word);
                //Inserting word in wordTree when all condition is met
            }
        }
    wordTree.printInorder(ofs);
    //Call print function in wordTree
    //Will print out word in order and the number of rotation required



}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that will check if userWord contain specific punctuation
//Function will also erase specific punctuation at the beginning and end of the userWord
bool checkPunct(string &userWord)
{
    char x=userWord.at(0);
    //variable x that store char at the beginning of userWord
    if(!isalpha(x))
    {
        //check if x is a punctuation
        if(x=='\"'||
                x=='(')
        {
            //2nd check to see if x is a punctuation
            userWord.erase(0,1);
            //delete that specific punctuation in userWord
        }
        else
        {
            //if x is not a specific punctuation
            if(x!='\'')
            {
                return true;
            }
        }
    }
    char y=userWord.at(userWord.length()-1);
    //variable y that store char at the end of the userWord
    if(!isalpha(y))
    {
        //check if y is a punctuation
        if(y==')'||
                y==','||
                y=='.'||
                y==';'||
                y==':'||
                y=='?'||
                y=='\"'||
                y=='!')
        {
            //2nd check if y is a specific punctuation
            userWord.erase(userWord.length()-1,1);
            //deleting that specific punctuation in the word
        }
        else
        {
            //if y is not that specific punctuation
            if(x!='\'')
            {
                return true;
            }
        }
    }
    for(int i=0; i<userWord.length(); i++)
        //for loop to check the rest of the word to see if they contain a specifics
    {
        if(!isalpha(userWord.at(i)))
        {
            //check if something in the word is punctuation
            if(userWord.at(i)=='\'')
            {
                //check if that specific punctuation is '
                return false;
            }
            return true;
        }
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that will check if userWord contain a number
bool checkNumber(string userWord)
{
    for(int i=0; i<userWord.length(); i++)
    {
        //loop that go through userWord
        if(isdigit(userWord.at(i)))
        {
            //Check if a specific a char in userWord is a digit
            return true;
        }

    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function that will erase any unnecessary whitespace
string eraseWS(string &userWord)
{
    //for loop that go through all char in a line and eliminate all whitespace
    int size = userWord.length();
    //variable that hold the userWord length
    for(int j = 0; j<=size; j++)
    //Loop that go through a word looking for whitespace
    {
        for(int i = 0; i <=j; i++)
        {
            if(userWord[i] == ' ' && userWord[i+1] == ' ')
            {
                userWord.erase(userWord.begin() + i);
            }
            else if(userWord[0]== ' ')
            {
                userWord.erase(userWord.begin());
            }
            else if(userWord[i] == '\0' && userWord[i-1]== ' ')
            {
                userWord.erase(userWord.end() - 1);
            }
        }
    }
    return userWord;
    //return word without unecessary whitespace
}
