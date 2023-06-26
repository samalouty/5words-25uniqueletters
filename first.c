#include <stdio.h>
#include <string.h>

int hasFiveDifferentLetters(const char* str) {
    int len = strlen(str);
    int count = 0;
    int letters[26] = { 0 };

    for (int i = 0; i < len; i++) {
        int index = str[i] - 'a';  
        if (!letters[index]) {
            letters[index] = 1;
            count++;
        }
    }

    return count == 5;
}

int main() {
    FILE* fpointer;
    fpointer = fopen("words.txt", "r");
    FILE* fp2 = fopen("wordsFiltered1.txt", "w"); 


    char singleLine[64];

    while (fgets(singleLine, sizeof(singleLine), fpointer)) {
        if (hasFiveDifferentLetters(singleLine)) {
            fputs(singleLine, fp2); 
        }
    }

    fclose(fpointer);

    return 0;
}
