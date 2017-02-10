//
//This program reads in words for a file, converts all letters to lower case,
//counts the words, and searches the file for words.
//
//This program is to be run by typing project1 followed by a file name,
//which includes text. 
//
//Author: Henry King
//CS 101
//Spring 2016

#include <iostream>
//#include <simpio>
#include <fstream>
#include <cctype>
using namespace std;

int verifyFile(int);
int firstWordPosition(string str);
int lengthInWords(string str);
int nextWordPosition(string str, int i);
string findAndDelete(string str, string word, int start);
int uniqueWords(string str);
void searchWords(string str);
void searchRegWord(string str, string word);

int main(int argc, char **argv)
    {
    if (verifyFile(argc) == 0) return 0; //verifies that a file name is given
                                         //on the command line
    ifstream infile;
    infile.open( argv[1] );
    if (infile.fail())                  //verifies the file given opens and is 
        {                               //not empty
        cout << "Error: could not open file." << endl;
        return 0;
        }

    
    string str;
    string next;
    string space = " ";
    
    getline(infile, str);
    while (infile.fail() == false)
        {
        getline(infile, next);
        str = str + space + next;
        }
    cout << "The number of words found in the file was ";
    cout << lengthInWords(str) << endl;
    int i;
    for (i = 0; i < str.length(); i++)  //convert all letters to lowercase
        {str[i] = tolower(str[i]);}
    cout << "The number of unique words found in the file was ";
    cout << uniqueWords(str) << endl;
    
    searchWords(str);

    infile.close();
    return 0;
    }





int uniqueWords(string str)
    {
    int words = 0;
    string current;
    int pos = firstWordPosition(str);
    while (pos < str.length() - 1)
        {
        while (isalpha(str[pos]))             //store current word in current
            {
            current += str[pos];
            pos++;
            }
        str = findAndDelete(str, current, pos); //find and delete all other 
        words++;                            //instances of current word
        current.clear();                    //clear current for next word
        pos = nextWordPosition(str,pos);    //start process over with next word
        }
    return words;
    }

string findAndDelete(string str, string word, int start)
    {
    int found;
    found = str.find(word,start);
    if (found == string::npos)
        return str;
    else
        if (isalpha( str[found + word.length()] ))
            {
            return findAndDelete(str,word,(found + word.length()));
            }
        else if ((found >= 1) && (isalpha(str[found - 1])))
                {
                return findAndDelete(str, word, (found + word.length()));
                }
        else
            str.erase(found, word.length());
            return findAndDelete(str,word,found);
    }

int lengthInWords(string str)
    {
    int words = 0;
    int pos = 0;
    pos = firstWordPosition(str);  //finds start of 1st word
    while(pos < str.length())
        {
        pos = nextWordPosition(str,pos);
        words++;
        }

    return words;
    }
    
int firstWordPosition(string str)
    {
    int i = 0;
    if (isalpha(str.at(i)) == 1)
        return i;
    while ( (isalpha(str.at(i)) == false) && (i <= str.length()) )
        {
        i++;
        }
    return i;                //i now holds position of start of first word
    } 

int nextWordPosition(string str, int i)
    {
    while ( (i < str.length()) && (isalpha(str.at(i)) == true) )
        i++;
    while ( (i < str.length()) && (isalpha(str.at(i)) == false) )
        {
        i++;
        }
    return i;
    } 
     
     
int verifyFile(int argc)   
    {
    if (argc == 1)    
        {
        cout << "Please enter \"project1\" ";
        cout << "followed by a file name" << endl;
        return 0;
        }
    return 1;
    }

void searchWords(string str)
    {
    string word;
    cout << endl;
    cout << endl;
    cout << "Please enter a word: (or enter \'EOF\' to stop)" << endl;
    cin >> word;
    if (word.compare("EOF") == 0)
        return;
    if (!(word.find("?") == string::npos))
        {
        cout << "this project does not handle words containing ?" << endl;
        searchWords(str);
        return;
        }
    else
        searchRegWord(str,word);
    searchWords(str);
    }

void searchRegWord(string str, string word)
    {
    int i = 0;
    int pos = 0;
    while (pos < str.length() && str.find(word, pos) != string::npos)
        {
        pos = str.find(word, pos);
        if ( ((pos == 0) || (pos >= 1 && isalpha(str[pos - 1]) == 0)) && (isalpha(str[pos + word.length()]) == 0))
            i++;    
        pos = str.find(word, pos) + word.length();
        }
    cout << "The word " << word << " appears " << i;
    cout << " times in the document" << endl;
    return;
    }

