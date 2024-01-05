/*
Tashfeen Abbasi
i22-2041
DS-D
Assignment 3
*/

#include "defination.h"

// Constructor for Node class
Node::Node(char x)
{

    data = x;
    left = NULL;
    right = NULL;
    up = NULL;
    down = NULL;
}

// Constructor for Notepad class
Notepad::Notepad()
{

    head = NULL;
}

void Notepad::insertAtCursor(char data)
{

    Node *newNode = new Node(data);

    // If this is the first node being inserted

    if (head == NULL)
    {
        head = newNode;
        cursor = newNode;
    }

    else
    {

        if (data == 13)
        {
            Node *temp = head;

            // loop until end of column
            while (temp->down != NULL)
            {
                temp = temp->down;
            }

            temp->down = newNode;
            newNode->up = temp;
        }
        else
        {
            // break the link between current and next node
            if (cursor->right)
            {

                cursor->right->left = newNode;
                newNode->right = cursor->right;
            }

            // create link between current node and new node
            cursor->right = newNode;
            newNode->left = cursor;

            // link upwards if possible
            if (cursor->up && cursor->up->right)
            {

                cursor->up->right->down = newNode;
                newNode->up = cursor->up->right;
            }
        }
    }

    // Update cursor to point to new node
    cursor = newNode;
}

void Notepad::deleteAtCursor()
{

    // Check if list is empty
    if (head == NULL || !cursor)
    {

        return;
    }

    // Save node to be deleted
    Node *del = cursor;

    // If this is not the first node of row
    if (cursor->left)
    {

        cursor->left->right = cursor->right;
    }

    else if (cursor->right)
    {

        // for first node of row
        head = cursor->right;
    }

    // If this is not the first node of column
    if (cursor->up)
    {

        cursor->up->down = cursor->down;
    }

    // Link up and down nodes
    if (cursor->down && cursor->up)
    {

        cursor->up->down = cursor->down;
        cursor->down->up = cursor->up;
    }

    // Update cursor
    if (cursor->left)
    {

        cursor = cursor->left;
    }

    else if (cursor->right)
    {

        cursor = cursor->right;
    }

    else if (head->down)
    {

        cursor = head->down;
    }

    else
    {

        cursor = NULL;
    }

    // Delete node
    delete (del);
}

// Print Notepad
void Notepad::print()
{
    // Starting from the head of the notepad

    Node *row = head;

    // Traverse through each row of the notepad

    while (row)
    {
        // Set a temporary node to the current row

        Node *temp = row;

        // Traverse through each element in the current row

        while (temp)
        {
            // Check if the current character is a new line character '\n'

            if (temp->data == '\n')
            {
                // Print a new line

                cout << endl;

                // Move to the next element in the row

                temp = temp->right;
                continue;
            }

            // Print the current character

            cout << temp->data;

            // Check if the current element is the cursor position

            if (temp == cursor)
            {
                // Mark the cursor position with '|'

                cout << "|";
            }

            // Move to the next element in the row

            temp = temp->right;
        }

        // Move to the next row

        cout << "\n";
        row = row->down;
    }
}

void Notepad::loadFromFile()
{
    // Open the file "file.txt" for reading

    ifstream file("file.txt");

    // Check if the file is successfully opened

    if (file.is_open())
    {
        char c;

        // Read each character from the file until the end is reached

        while (file.get(c))
        {
            // Check if the character is a new line character '\n'

            if (c == '\n')
            {
                // Call the insertAtCursor() function to start a new line in the text editor (assuming it exists)

                insertAtCursor(13);
            }
            else
            {
                // Call the insertAtCursor() function to insert the character at the current cursor position in the text editor (assuming it exists)

                insertAtCursor(c);
            }
        }

        // Print a success message indicating that the text has been loaded successfully

        cout << "Text loaded successfully" << endl;

        // Close the file

        file.close();
    }
    else
    {
        // Print an error message if the file cannot be opened

        cout << "Unable to open file" << endl;
    }
}

void Notepad::saveToFile()
{
    // Open the file "file.txt" for writing

    ofstream file("file.txt");

    // Check if the file is successfully opened

    if (file.is_open())
    {
        // Start from first character after head.

        Node *temp = head->right;

        // Traverse through the linked list horizontally

        while (temp != NULL)
        {
            Node *temp2 = temp;

            // Traverse through the linked list vertically

            while (temp2)
            {
                // Write each character to the file

                file << temp2->data;
                temp2 = temp2->right;
            }

            // Add a newline character '\n' after each row in the text editor

            file << "\n";

            // Move down to the next row

            temp = temp->down;
        }

        // Print a success message indicating that the text has been saved successfully

        cout << "Text saved Successfully" << endl;

        // Close the file

        file.close();
    }
    else
    {
        // Print an error message if the file cannot be opened

        cout << "Unable to open file" << endl;
    }
}

void Notepad::moveCursorUp()
{
    // Check if the cursor has an up neighbor

    if (cursor->up != nullptr)
    {
        // Update the cursor to point to the up neighbor

        cursor = cursor->up;
    }
}

void Notepad::moveCursorDown()
{
    // Check if the cursor has a down neighbor

    if (cursor->down != nullptr)
    {
        // Update the cursor to point to the down neighbor

        cursor = cursor->down;
    }
}

void Notepad::moveCursorLeft()
{
    // Check if the cursor has a left neighbor

    if (cursor->left != nullptr)
    {
        // Update the cursor to point to the left neighbor

        cursor = cursor->left;
    }
}

void Notepad::moveCursorRight()
{
    // Check if the cursor has a right neighbor

    if (cursor->right != nullptr)
    {
        // Update the cursor to point to the right neighbor

        cursor = cursor->right;
    }
}

void Notepad::checkwords(Dictionary &dict)
{
    // Create a vector to store the words found in the notepad

    vector<string> words;

    // Set a temporary pointer to point to the right neighbor of the head node

    Node *temp = head->right;

    // Iterate through the rows of the notepad

    while (temp != NULL)
    {
        // Create a string to store the current word being checked

        string currentWord;

        // Set a current pointer to the temporary pointer

        Node *current = temp;

        // Iterate through the columns of the notepad

        while (current != NULL)
        {
            // Check if the data in the current node is a space character

            if (current->data == ' ')
            {
                // Check if the current word is not empty

                if (!currentWord.empty())
                {
                    // Add the current word to the vector of words and clear the currentWord variable

                    words.push_back(currentWord);
                    currentWord.clear();
                }
            }
            else
            {
                // Append the character in the current node to the currentWord

                currentWord += current->data;
            }

            // Move the current pointer to the right neighbor

            current = current->right;
        }

        // Check if the current word is not empty after finishing a row

        if (!currentWord.empty())
        {
            // Add the current word to the vector of words

            words.push_back(currentWord);
        }

        // Move the temporary pointer to the down neighbor

        temp = temp->down;
    }

    // Initialize an index variable i to iterate through the vector of words

    int i = 0;
    while (i < words.size())
    {
        // Call the CheckSpelling function to check the spelling of each word in the dictionary

        CheckSpelling(words[i], dict);

        // Increment the index variable i

        i++;
    }
}

void Notepad::run(Dictionary &dict)
{

    char ch;

    while (true)
    {
        // Converting character to corresponding ascii value .........

        int key = static_cast<int>(ch);
        int arrow;

        switch (key)
        {

        case -32:

            // For Arrows

            ch = _getch();
            arrow = static_cast<int>(ch);

            // CheckOut for 2nd value in arrow

            if (arrow == 72)
            {
                // UP.......

                moveCursorUp();
            }
            else if (arrow == 80)
            {
                // DOWN..........

                moveCursorDown();
            }
            else if (arrow == 75)
            {
                // LEFT.........

                moveCursorLeft();
            }
            else if (arrow == 77)
            {
                // RIGHt...........

                moveCursorRight();
            }
            break;

        case 8:

            // For Backspace

            deleteAtCursor();
            break;

        case 19:

            // For CTRL + S

            saveToFile();
            break;

        case 12:

            // For CTRL + L

            loadFromFile();
            break;

        case 27:

            // For ESC

            saveToFile();
            cout << "Exitting Notepad ........" << endl;
            return;
            break;

        default:
            insertAtCursor(ch);
            break;
        }

        print();

        cout << endl
             << endl;

        cout << "Words suggestion" << endl;

        checkwords(dict);

        ch = _getch();

        system("cls");
    }
}

// Constructor for Dictionary class
Dictionary::Dictionary(const string &dictionaryFile)
{

    LoadDictionary(dictionaryFile);
}

// Method to load dictionary from file
void Dictionary::LoadDictionary(const string &dictionaryFile)
{

    ifstream file(dictionaryFile);

    if (!file.is_open())
    {
        // If file failed to open
        cout << "Failed to load file" << endl;
        return;
    }

    string word;
    while (file >> word)
    {
        // Read words from file
        dictionary.push_back(word);
    }

    file.close();
}

// Method to check whether a word is in the dictionary

bool Dictionary::IsWordInDictionary(const string &word)
{
    // Iterate over each word in the dictionary

    for (const string &dictWord : dictionary)
    {
        // Check if the current word matches the given word

        if (dictWord == word)
        {
            // Word found in dictionary

            return true;
        }
    }

    // Word not found in dictionary

    return false;
}

// Print Dictionary
void Dictionary::print()
{
    for (int i = 0; i < dictionary.size(); i++)
    {
        // Output the current word in the dictionary
        cout << dictionary[i];

        // Move to the next line
        cout << endl;
    }
}

// Get the dictionary
const vector<string> &Dictionary::GetDictionary() const
{
    // Return a constant reference to the dictionary vector

    return dictionary;
}

// Method to check spelling of a word
void CheckSpelling(const string &misspelledWord, const Dictionary &dict)
{
    // Create a new vector containing all the words from the dictionary

    vector<string> words(dict.GetDictionary().begin(), dict.GetDictionary().end());

    // Iterate through each word in the dictionary

    for (int i = 0; i < words.size(); i++)
    {
        // Get the current word

        string word = words[i];

        // Check if the misspelled word matches the current word

        if (misspelledWord == word)
        {
            // The word is spelled correctly, so return without printing any suggestions

            return;
        }
    }

    // Print the misspelled word followed by "=>"

    cout << misspelledWord << " => ";

    // Iterate through each word in the dictionary again

    for (int i = 0; i < words.size(); i++)
    {
        // Get the current word

        string word = words[i];

        // Check if the lengths of the misspelled word and current word are the same

        if (misspelledWord.length() == word.length())
        {
            // Letter Substitution

            // Initialize a counter to keep track of the number of differing characters

            int diffCount = 0;

            // Iterate over each character in the word

            for (int i = 0; i < word.length(); ++i)
            {
                // If the characters at the same position differ

                if (misspelledWord[i] != word[i])
                {
                    // Increment the difference count

                    diffCount++;

                    // If there are more than one differences, exit the loop

                    if (diffCount > 1)
                    {
                        break;
                    }
                }
            }

            // If there is only one difference

            if (diffCount == 1)
            {
                // Print the current word as a suggestion

                cout << word << " ";
            }

            // Letter Reversal
            // Reset the difference count
            diffCount = 0;

            // Iterate over each character in the word, except the last one

            for (int i = 0; i < word.length() - 1; ++i)
            {
                // If the characters at the current position and next position are not equal when reversed

                if (misspelledWord[i] != word[i + 1] || misspelledWord[i + 1] != word[i])
                {
                    // Increment the difference count

                    diffCount++;

                    // If there are more than one differences, exit the loop

                    if (diffCount > 1)
                    {
                        break;
                    }
                }
            }

            // If there is only one difference

            if (diffCount == 1)
            {
                // Print the current word as a suggestion

                cout << word << " ";
            }
        }

        // Check if the length of the misspelled word is one less than the current word

        else if (misspelledWord.length() == word.length() - 1)
        {
            // Letter Omission
            // Iterate over each character in the word
            for (int i = 0; i < word.length(); ++i)
            {
                // Create an empty temporary string

                string temp = "";

                // Construct the temp string without the character at position i
                for (int j = 0; j < word.length(); ++j)
                {
                    // Exclude the character at position i

                    if (j != i)
                    {
                        // Add the character to the temporary string

                        temp += word[j];
                    }
                }

                // If the temporary string matches the misspelled word

                if (temp == misspelledWord)
                {
                    // Print the current word as a suggestion

                    cout << word << " ";
                    break;
                }
            }
        }

        // Check if the length of the misspelled word is one more than the current word

        else if (misspelledWord.length() == word.length() + 1)
        {
            // Letter Insertion

            // Iterate over each position in the word, including the end
            for (int i = 0; i <= word.length(); ++i)
            {
                // Iterate over each possible character to insert

                for (char ch = 'a'; ch <= 'z'; ++ch)
                {
                    // Create an empty temporary string

                    string temp = "";

                    // Construct a new string with the letter ch inserted at the ith position

                    for (int j = 0; j <= word.length(); ++j)
                    {
                        // If the current position is the insertion position

                        if (j == i)
                        {
                            // Insert the character into the temporary string

                            temp += ch;
                        }

                        // Append the characters from the original word to the temporary string

                        if (j < word.length())
                        {
                            temp += word[j];
                        }
                    }

                    // If the temporary string matches the misspelled word

                    if (temp == misspelledWord)
                    {
                        // Print the current word as a suggestion

                        cout << word << " ";
                        break;
                    }
                }
            }
        }
    }

    // Move to the next line after printing all the suggestions

    cout << endl;
}
