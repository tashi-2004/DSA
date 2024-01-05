/*
Tashfeen Abbasi
i22-2041
DS-D
Assignment 3
*/
#include <iostream>
#include "functions.cpp"

int main()
{
    Notepad list;
    Dictionary dictionary("dictionary.txt");
    list.run(dictionary);
    return 0;
}
