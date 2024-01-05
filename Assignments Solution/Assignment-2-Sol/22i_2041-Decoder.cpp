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
    // Set the filename for the codes file
    string codesFilename = "Codes.txt";

    // Create a decoder object and initialize it with the codes file
    decoder myDecoder(codesFilename);

    // Set the filenames for the encoded and decoded files
    string encodedFilename = "Encoded.bin";
    string decodedFilename = "Decoded.txt";

    // Decode the encoded file using the codes and save the result to the decoded file
    myDecoder.decodeAndSave(encodedFilename, decodedFilename);

    return 0;
}
