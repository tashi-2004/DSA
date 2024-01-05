/*
Tashfeen Abbasi
i22-2041
DS-D
Assignment 3
*/
#include <iostream> // For input/output operations
#include <fstream> // For file handling operations
#include <bitset> // For bitwise operations
#include <string> // For string operations
#include <sstream> // For string stream operations

using namespace std;

// Struct to represent a node in the tree
struct Node
{
    char character; // The character represented by this node
    int freq; // Frequency of the character
    Node *Left; // Pointer to the left child node
    Node *Right; // Pointer to the right child node
    Node *next; // Pointer to the next node in the priority queue
    string Code; // code for the character

    Node(char ch); // Constructor with character parameter

    Node(char ch, int fq); // Constructor with character and frequency parameters

};

// Class to implement a priority queue for the nodes
class Priority_Queue
{
public:
    Node *head; // Pointer to the head of the priority queue

    Priority_Queue(); // Constructor

    void add(Node *node); // Method to add a node to the priority queue

    void remove(); // Method to remove the first node from the priority queue

    void bubble_sort(); // Method to sort the nodes in the priority queue based on their frequencies

    void swap_nodes(Node *first, Node *second); // Method to swap two nodes in the priority queue

    bool isEmpty(); // Method to check if the priority queue is empty

    Node *mergeNodesIteratively(); // Method to merge nodes iteratively and return the root node of the tree

    Node *createNode(char ch, int tot); // Method to create a new node with given character and total frequency

};

// Function to compare two nodes based on their frequencies
bool compare(Node *Node1, Node *Node2);

// Function to calculate the frequency of characters in the given text and construct the priority queue
void calculate_frequency(const string &text, Node *&head);

// Function to create a new node with given character and frequency
Node *create_node(char character, int frequency);

// Function to merge two nodes and return the root node of the merged tree
Node *merge_nodes(Node *node1, Node *node2);

// Function to read the contents of a file and return it as a string
string read_file(const string &filename);

// Function to assign codes to each node in the tree
void assignCodes(Node *root, string code);

// Function to print the characters and their codes in the tree
void Print(Node *root);

// Helper function to recursively save the codes to an output file
void SaveCodesHelper(Node *root, ofstream &outputFile);

// Function to save the codes to an output file
void SaveCodes(Node *root);

// Function to get the code for a given character from the tree
string getCode(const Node *root, char character);

// Function to save the encoded data to a file using the tree
void saveEncoded(string data, Node *root);

// Function to save the decoded data to a file using the tree
void saveOutput(string data, Node *root);

// Struct to represent a node in the linked list of codes
struct CodeNode
{
    char letter; // The character represented by this code
    string code; // The code for the character
    CodeNode *next; // Pointer to the next code node in the linked list

    CodeNode(char l, const string &c); // Constructor with character and code parameters

};

// Class to implement a decoder for the codes
class decoder
{
private:
    CodeNode *codes; // Pointer to the head of the linked list of codes

public:
    decoder(const string &codesFilename); // Constructor to initialize the decoder with a file containing the codes

    ~decoder(); // Destructor to free memory used by the linked list of codes

    void readCodes(const string &codesFilename); // Method to read the codes from a file and construct the linked list

    void decodeAndSave(const string &encodedFilename, const string &decodedFilename); // Method to decode the encoded data and save it to a file

};
