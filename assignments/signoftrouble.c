#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// max # of chars that can be read as input (including terminating null char)
#define MAX_CHAR 100002
#define ASCII_SIZE 128

// Rough Structure of program

/*
    1. Get old user input for old sign message (all caps, make sure to account spaces) FGETS
    2. Store user input in a const char array
    3. Get user input for new sign message
    4. Store into another const char array 
    5. Use string methods (strcmp) to find all values = 0 (equal), ignore -1 and 1
    6. Use iteration, for each 0 comparison strcmp, increment a counter
    7. Upon ending program, return the counter value
*/

char *allocateString(int size);



int main(void){
    char *inputString = allocateString(MAX_CHAR);
    char *freqArray1 = allocateString(ASCII_SIZE);
    char *freqArray2 = allocateString(ASCII_SIZE);

    printf("%s", "ENTER ORIGINAL MESSAGE: ");
    fgets(inputString, MAX_CHAR, stdin);

    for(int i = 0; i < strlen(inputString); i++){
        freqArray1[(int)inputString[i]]++;
    }
 
    for(int i = 0; i < ASCII_SIZE; i++){
        printf("%d, %d\n", i,freqArray1[i]);
    }

    //char *newString = malloc(MAX_CHAR*sizeof(char));

    return 0;
}

char *allocateString(int size){
    char *string = malloc(size*sizeof(char));

    return string; 
}
