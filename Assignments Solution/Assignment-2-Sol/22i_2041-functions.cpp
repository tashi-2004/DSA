/*
Tashfeen Abbasi
i22-2041
DS-D
Assignment 3
*/

#include "defination.h"

// Basic Constructor using character

Node::Node(char ch)
{
    character = ch;
    freq = 1;
    Left = NULL;
    Right = NULL;
    next = NULL;
    Code = "";
}

// Constructor using both character and frequency

Node::Node(char ch, int fq)
{
    character = ch;
    freq = fq;
    Left = NULL;
    Right = NULL;
    next = NULL;
    Code = "";
}

// Priority Queue constructor

Priority_Queue::Priority_Queue()
{
    head = NULL;
}

// Comparison function to compare for N1<N2

bool compare(Node *Node1, Node *Node2)
{
    if (Node1->freq < Node2->freq)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Add Function of Priority Queue that uses Node

void Priority_Queue::add(Node *node)
{
    Node *newNode = new Node(node->character, node->freq);
    newNode->next = head;
    head = newNode;
}

// Remove Function that always remove from top

void Priority_Queue::remove()
{
    if (head == NULL)
    {
        cout << "Priority Queue is empty. Cannot remove." << endl;
        return;
    }
    Node *temp = head;
    head = head->next;
    delete temp;
}

// Bubble sort in order to prioritize

void Priority_Queue::bubble_sort()
{
    Node *current;
    Node *next;
    bool swapped;

    do
    {
        swapped = false;
        current = head;

        while (current != NULL && current->next != NULL)
        {
            next = current->next;

            if (current->freq > next->freq)
            {
                swap_nodes(current, next);
                swapped = true;
            }

            current = next;
        }
    } while (swapped);
}

// Swapping data of 2 Nodes inside Queue

void Priority_Queue::swap_nodes(Node *first, Node *second)
{
    int temp_tot = first->freq;
    first->freq = second->freq;
    second->freq = temp_tot;

    char temp_ch = first->character;
    first->character = second->character;
    second->character = temp_ch;
}

// Check for empty

bool Priority_Queue::isEmpty()
{
    return head == NULL;
}

// Merging and making a Tree

Node *Priority_Queue::mergeNodesIteratively()
{
    while (head != NULL && head->next != NULL)
    {
        Node *Node1 = head;
        Node *Node2 = head->next;

        int sumFreq = Node1->freq + Node2->freq;
        Node *newNode = new Node('-', sumFreq);
        if (Node1->freq < Node2->freq)
        {
            newNode->Left = Node1;
            newNode->Right = Node2;
        }
        else
        {
            newNode->Left = Node2;
            newNode->Right = Node1;
        }
        newNode->next = Node2->next;
        Node2->next = newNode;
        head = head->next->next;
    }

    return head;
}

// Creation of Node

Node *Priority_Queue::createNode(char ch, int tot)
{
    return new Node(ch, tot);
}

// Calculating Frequency in start for each alphabet

void calculate_frequency(const string &text, Node *&head)
{
    int i = 0;
    while (text[i] != '\0')
    {
        Node *current = head;
        bool found = false;

        while (current != NULL)
        {
            if (current->character == text[i])
            {
                current->freq++;
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found)
        {
            Node *newNode = new Node(text[i]);
            newNode->next = head;
            head = newNode;
        }
        i++;
    }
}

// Creation of Node

Node *create_node(char character, int frequency)
{
    Node *node = new Node(character, frequency);
    return node;
}

// Merging of Nodes

Node *merge_nodes(Node *node1, Node *node2)
{
    Node *merged_node = create_node('\0', node1->freq + node2->freq);
    if (compare(node1, node2))
    {
        merged_node->Left = node1;
        merged_node->Right = node2;
    }
    else
    {
        merged_node->Left = node2;
        merged_node->Right = node1;
    }
    return merged_node;
}

// reading of File through file name and return string

string read_file(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return "";
    }

    string content;
    char ch;
    while (file.get(ch))
    {
        content += ch;
    }

    file.close();
    return content;
}

// Assigning codes to the Nodes in Tree

void assignCodes(Node *root, string code)
{
    if (root == NULL)
    {
        return;
    }
    root->Code = code;
    assignCodes(root->Left, code + "0");
    assignCodes(root->Right, code + "1");
}

// Printing of Tree (Just did in order to proceed)

void Print(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    Print(root->Left);
    if (root->character != '-')
    {
        cout << root->character << "\t" << root->freq << "\t" << root->Code << endl;
    }
    Print(root->Right);
}

// Helper code to save codes using recursion

void SaveCodesHelper(Node *root, ofstream &outputFile)
{
    if (root == NULL)
    {
        return;
    }
    SaveCodesHelper(root->Left, outputFile);
    if (root->character != '-')
    {
        outputFile << root->character << "\t" << root->Code << endl;
    }
    SaveCodesHelper(root->Right, outputFile);
}

// Main Saving of codes to a file

void SaveCodes(Node *root)
{
    string filename = "Codes.txt";
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        cout << "Error opening file: " << filename << endl;
        return;
    }

    SaveCodesHelper(root, outputFile);

    outputFile.close();
}

// Getter or code using recursive calls

string getCode(const Node *root, char character)
{
    if (root == NULL)
    {
        return "";
    }
    if (root->character == character)
    {
        return root->Code;
    }
    string leftCode = getCode(root->Left, character);
    if (!leftCode.empty())
    {
        return leftCode;
    }
    return getCode(root->Right, character);
}

// Saving the output ......

void saveOutput(string data, Node *root)
{
    int i = 0;
    ofstream outputFile("Output.txt");
    if (!outputFile.is_open())
    {
        cout << "Error opening file: "
             << "Encoded.txt" << endl;
        return;
    }

    while (data[i] != '\0')
    {
        string code = getCode(root, data[i]);
        outputFile << code;
        i++;
    }
    outputFile.close();
}

// Saving of Encoded text into a bin file

void saveEncoded(string data, Node *root)
{
    ofstream outputFile("Encoded.bin", ios::binary);
    if (!outputFile.is_open())
    {
        cout << "Error opening file: Encoded.bin" << endl;
        return;
    }

    int i = 0;

    for (i; data[i] != '\0'; i++)
    {
        string code = getCode(root, data[i]);

        bitset<8> byte(code);
        char byteChar = static_cast<char>(byte.to_ulong());
        outputFile.write(&byteChar, sizeof(char));
    }

    outputFile.close();
}

// CodeNode class constructor

CodeNode::CodeNode(char l, const string &c)
{
    letter = l;
    code = c;
    next = NULL;
}

// Decoder Class constructor

decoder::decoder(const string &codesFilename)
{
    codes = NULL;
    readCodes(codesFilename);
}

// Destructor for Decoder Class

decoder::~decoder()
{
    CodeNode *current = codes;
    while (current != NULL)
    {
        CodeNode *next = current->next;
        delete current;
        current = next;
    }
}

// Reading of Codes through File and assign its letter and string

void decoder::readCodes(const string &codesFilename)
{
    ifstream codesFile(codesFilename);

    if (!codesFile.is_open())
    {
        cout << "Error opening codes file: " << codesFilename << endl;
        return;
    }

    CodeNode *tail = NULL;
    string line;
    while (getline(codesFile, line))
    {
        char letter;
        string code;
        istringstream iss(line);
        iss >> letter;
        iss.ignore(); // Ignore the tab separator
        iss >> code;

        if (codes == NULL)
        {
            codes = new CodeNode(letter, code);
            tail = codes;
        }
        else
        {
            tail->next = new CodeNode(letter, code);
            tail = tail->next;
        }
    }

    codesFile.close();
}

// Decoding and saving of File

void decoder::decodeAndSave(const string &encodedFilename, const string &decodedFilename)
{
    ifstream encodedFile(encodedFilename, ios::binary);
    ofstream decodedFile(decodedFilename);

    if (!encodedFile.is_open())
    {
        cout << "Error opening encoded file: " << encodedFilename << endl;
        return;
    }

    if (!decodedFile.is_open())
    {
        cout << "Error opening decoded file: " << decodedFilename << endl;
        return;
    }

    CodeNode *currentCode = codes;
    char byte;

    while (encodedFile.read(&byte, 1))
    {
        string byteCode = bitset<8>(byte).to_string();

        string code1 = "";
        bool flag = false;

        for (int i = 0; i < 8; i++)
        {
            while (byteCode[i] != '1' && i < 7 && !flag)
            {
                i++;
            }
            flag = true;
            code1 += byteCode[i];
        }

        CodeNode *temp = codes;
        while (temp != NULL)
        {
            if (temp->code == code1)
            {
                decodedFile << temp->letter;
                cout << temp->letter;
                break;
            }
            temp = temp->next;
        }
    }

    encodedFile.close();
    decodedFile.close();
}