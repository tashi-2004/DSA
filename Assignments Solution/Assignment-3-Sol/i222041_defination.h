//Libraries to work with..................

/*
Tashfeen Abbasi
i22-2041
DS-D
Assignment 3
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

//Dictionary class to store and work with vector of strings.............................

class Dictionary
{

//Data member of dictionary.......................

private:
    vector<string> dictionary;

//Functions to use with .................

public:

    //Constructor..................

    Dictionary(const string &dictionaryFile);

    //Check for word...............

    bool IsWordInDictionary(const string &word);

    //Loading the dictionary from file..............
    void LoadDictionary(const string &dictionaryFile);

    //Getters for it .................
    const vector<string> &GetDictionary() const;

    //Print used to see wether it is loaded or not ..............

    void print();

};

//Node

struct Node
{

    //Char for storing data...............

    char data;

    //2D Links (TOP,BOTTOM,LEFT,RIGHT)...........

    Node *left;
    Node *right;
    Node *up;
    Node *down;

    //Constructor............

    Node(char x);
};

//Notepad Class..............

class Notepad
{

//Data members...............

private:

    //Head for start and cursor for control over .............

    Node *head;
    Node *cursor;

//Functions..........

public:

    //Constructor...............

    Notepad();

    //Insertion at cursor pointing ..............

    void insertAtCursor(char data);

    //Printing of data in notepad..............

    void print();

    //Deletion at cursor ...............

    void deleteAtCursor();

    //Main code for notepad ...............

    void run(Dictionary &dict);

    //Movement of cursors .............

    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();

    //Loading data into notepad from file ...............

    void loadFromFile();

    //Saving data from notepad to file ..............

    void saveToFile();

    //Checking and suggesting all the words in notepad by comparing it to dictionary ..............

    void checkwords(Dictionary &dict);

};

//Function for suggestion .............

void CheckSpelling(const string &misspelledWord, const Dictionary &dict);