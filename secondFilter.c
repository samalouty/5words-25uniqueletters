#include <stdio.h>
#include <string.h>

int areAnagrams(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2) {
        return 0; 
    }

    int count1[256] = { 0 };
    int count2[256] = { 0 };

    for (int i = 0; i < len1; i++) {
        count1[(int)str1[i]]++; // increment the count of characters in str1
        count2[(int)str2[i]]++; // increment the count of characters in str2
    }

    for (int i = 0; i < 256; i++) {
        if (count1[i] != count2[i]) {
            return 0; 
        }
    }

    return 1; 
}

int noAnagram(const char* str, const char* filename) {
    FILE* fpointer = fopen(filename, "r");
    char line[64];

    while (fgets(line, sizeof(line), fpointer)) {
        line[strcspn(line, "\n")] = '\0'; 
        
        if (areAnagrams(str, line)) {
            fclose(fpointer);
            return 0; // found an anagram, so return 0
        }
    }

    fclose(fpointer);
    return 1; // no anagram found, return 1
}

int main() {
    FILE* inputFile;
    FILE* outputFile;

    inputFile = fopen("wordsFiltered1.txt", "r");
    outputFile = fopen("NoAnagram.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }

    char singleLine[64];

    while (fgets(singleLine, sizeof(singleLine), inputFile)) {
        singleLine[strcspn(singleLine, "\n")] = '\0'; 

        if (noAnagram(singleLine, "NoAnagram.txt")) {
            fputs(singleLine, outputFile);
            fputc('\n', outputFile); // add a newline character after each word
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
