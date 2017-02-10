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
void searchVariableWord(string str, string word, int pos);
int isWordMatch(string str, string word, int strPos);
int charCompare(string str, string word, int strPos, int wordPos);
string findPrintAndDelete(string str, string word, int start);
string findMatchingWord(string str, string word, int pos);
int handleQuestionMark(string str, string word, int &strPos, int &wordPos);
int countQuestionMarks(string word, int pos);

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
    //str = findAndDelete(str, "the",0);
    cout << "The number of unique words found in the file was ";
    cout << uniqueWords(str) << endl;
    
    cout << str << endl;
    
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
    if (word.find("?") == string::npos)
        {
        searchRegWord(str, word);
        searchWords(str);
        }
    else
        searchVariableWord(str, word, 0);
        searchWords(str);
        return;
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

void searchVariableWord(string str, string word, int pos)
    {
    int found = 0;
    int wordsFound = 0;
    string matchingWord;
    if (word[0] == '?')                 //find first instance of first char
        {                                 //in word and store in variable pos
        while (isalpha(str[pos]) == 0)
            pos++;
        found = pos;
        cout << "1" << endl;
        }
    else
        found = str.find(word[0], pos); //found now holds position of first
                                        //possible matching word
    while (!isWordMatch(str, word, pos))    //increase pos until a match is found 
        {                                   //or end of string is reached
        pos++;  
        if (pos == str.length())    //return if the end of string is reached
            return;
cout << "2" << endl;
        }
                              //at this point pos is a matching word
        matchingWord = findMatchingWord(str, word, pos);
cout << "3" << endl;

        str = findPrintAndDelete(str, matchingWord, pos); //delete all instances
                                     //of the matching word and print how many
        searchVariableWord(str, word, pos); //continue searching for a different
                                            //matching word
    return;
    }




int isWordMatch(string str, string word, int strPos)
    {
cout << "4" << endl;
    int wordPos = 0;
    int numQuestionMarks = 0;
    while (wordPos < word.length())
        {
cout << "5" << endl;
        if (strPos == str.length())
            return 0;
        //compare to string pos
        //if the same increment strPos and wordPos
    //if its a question mark call handle questionmarks,
    //if it returns one for match, increment wordPos and strPos
    //increment wordPos and strPos
        //if its not the same, 
    //if not a letter or ? return 0

    //keep doing this until the end of the word is reached.
    //if at the end, the next char is a letter (not independent word)
    //return 0, else return 1.
        if (str[strPos] == word[wordPos])
            {
            strPos++;
            wordPos++;
            }
        else if( word[wordPos] == '?' )
            {
            if (handleQuestionMark(str, word, strPos, wordPos) == 0)
                return 0;
            }
        wordPos++;
        strPos++;
        }
    return 1;
    }

int handleQuestionMark(string str, string word, int &strPos, int &wordPos)
    {
cout << "6" << endl;
    int numQuestionMarks = countQuestionMarks(word, wordPos);
    int toEndOfWord = 0;
    int middleOfWord = 1;
    int i;
    char next;
    int originalStrPos = strPos;
    int originalWordPos = wordPos;
    if (numQuestionMarks + wordPos == word.length()) //if the question marks
        {                       //go to the end of the word,
        while (strPos < str.length() && wordPos < word.length() ) //and all
            {    //chars in the string are letters to the end of the word
cout << "7" << endl;
            if (!isalpha(str[strPos]) ) 
                {middleOfWord = 0;}
            strPos++;
            wordPos++;
            }
        if (middleOfWord == 1)          //make sure the next char is not a 
            {                           //letter 
            if (strPos < str.length() && isalpha(str[strPos] + 1) )
                return 0; //because it is a match, but not an independent word
            else 
                {
                strPos++;
                wordPos++;
                return 1; //because it is a match and an independent word
                }
            }
        }
    //if the ?'s don't continue to end of word, go to next non ? and store
    //in next. Check the next (numQuestionMarks) characters to see if 
    //they match with next. If so then continue searching at strPos and 
    //wordPos
    else
        {
        wordPos = originalWordPos;
        strPos = originalStrPos;
        next = word[wordPos + numQuestionMarks];
        i = numQuestionMarks;
        while ( i >= 0 )     
            {
cout << "8" << endl;
            if( strPos < str.length() && str[strPos + i] == next )
                {
                strPos++;
                wordPos++;
                return 1;
                }
            i = i - 1;
            }
        
        return 0;
        }
    return 0;
    //if the next character in the string is the same,
    //increment wordPos and strPos
    }

//Counts number of question marks in a row starting at pos "pos"    
int countQuestionMarks(string word, int pos)
    {
cout << "9" << endl;
    int numQuestionMarks = 0;
    while ('?' == word[pos])
        {
        numQuestionMarks++;
        pos++;
        }
    return numQuestionMarks;
    }

string findMatchingWord(string str, string word, int pos)
    {
cout << "10" << endl;
    string matchingWord = "";
    int i = pos;
    for(i = pos; i < pos + 5; i++)
        matchingWord += str[i];
    
    return matchingWord;
    }

int charCompare(string str, string word, int strPos, int wordPos)
    {
    if (word[wordPos] == '?' && isalpha(str[strPos]))
        return 1;
    else if (str[strPos] == word[wordPos])
        return 1;
    else
        return 0;
    }

//This function uses recursion to search
//string "str" to see if it contains the string "word"
//starting at position "start". 
//It prints the number of instances (that are stand alone words)found and 
//deletes all instances of the word after the start position.
//It returns the remaining string.
string findPrintAndDelete(string str, string word, int start)
    {
cout << "11" << endl;
    int times = 0;
    int found;                          //find first instance of "word"
    found = str.find(word,start);       //and store position in pos
    if (found == string::npos)  //if not found, return the string and print
        {                       //the number of times "word has been found
   cout << "The word " << word << " appears " << times << "times";
        cout << " in the document" << endl;
        return str;
        }
    else
        if (isalpha( str[found + word.length()] ))  //if char after word
            {               //is a letter, not an independent word
            return findAndDelete(str,word,(found + word.length()));
            }
        else if ((found >= 1) && (isalpha(str[found - 1]))) //if char before
                {           //word is a letter, not an independent word
                return findAndDelete(str, word, (found + word.length()));
                }
        else                //else it is an independent word
            times++;
            str.erase(found, word.length());
            return findAndDelete(str,word,found);
    }

