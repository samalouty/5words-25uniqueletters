#include <stdio.h>
#include <string.h>

unsigned int wordToBinary(const char* word) {
    int length = strlen(word);
    unsigned int binary = 0;

    for (int i = 0; i < length; i++) {
        int shift = word[i] - 'a';
        binary |= (1u << shift); 
    }

    return binary;
}

void binaryToWord(unsigned int binary, char* word) {
    memset(word, '\0', 27); 
    int index = 0;

    for (int i = 0; i < 26; i++) {
        if (binary & (1u << i)) {
            word[index] = 'a' + i; 
            index++;
        }
    }
}

int main() {
    FILE* inputFile;
    FILE* outputFile;

    inputFile = fopen("NoAnagram.txt", "r");
    outputFile = fopen("binaryRep.txt", "w");

    char singleLine[64];
    char binaryString[27];

    while (fgets(singleLine, sizeof(singleLine), inputFile)) {    
        unsigned int binary = wordToBinary(singleLine);
        fprintf(outputFile, "%u\n", binary);           // converting numbers to a custom binary representation 
    }


    fclose(inputFile);
    fclose(outputFile);


    return 0;
}