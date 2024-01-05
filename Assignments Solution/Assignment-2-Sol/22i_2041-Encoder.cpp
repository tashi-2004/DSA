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
    // Read the contents of the file into a string variable
    string filename = "file.txt";
    string data = read_file(filename);

    // Calculate the frequency of characters in the data
    Node *frequencies = NULL;
    calculate_frequency(data, frequencies);

    // Create a priority queue and add the frequency nodes to it
    Priority_Queue pq;
    Node *temp = frequencies;
    while (temp != NULL)
    {
        pq.add(temp);
        temp = temp->next;
    }

    // Sort the priority queue using bubble sort
    pq.bubble_sort();

    // Merge the nodes in the priority queue to create a tree
    Node *tree = pq.mergeNodesIteratively();

    // Assign codes to each character in the tree
    assignCodes(tree, "");

    // Print the tree structure
    Print(tree);

    // Save the character codes to a file
    SaveCodes(tree);

    // Save the original data along with the character codes
    saveOutput(data, tree);

    // Save the encoded data using the character codes
    saveEncoded(data, tree);

    return 0;
}
