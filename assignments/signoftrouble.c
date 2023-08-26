// Jake Lille
// COP3502
// 8/25/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// max # of chars that can be read as input (including terminating null char)
#define MAX_CHAR 100002
#define ASCII_SIZE 128

// function prototypes
int *allocateString(int size);

int compareFreq(int *freq1, int *freq2);

int main(void){
    //temp string for input,  make sure 100002 chars allocated
    char *inputString = malloc(MAX_CHAR*sizeof(char));
    //init 2 freq arrays via. function, passing ASCII size of 128
    int *freqArray1 = allocateString(ASCII_SIZE);
    int *freqArray2 = allocateString(ASCII_SIZE);
    
    //prompt user, read input via. fgets from stdin stream
    printf("%s", "ENTER ORIGINAL MESSAGE: ");
    fgets(inputString, MAX_CHAR, stdin);

    //strlen once (efficiency)
    int len = strlen(inputString);

    //fill freq array with ASCII values
    // IGNORE 10 (\n) and 32 (space) as we don't need these as letters
    // 65 - 90 uppercase ASCII (MAKE SURE TO INCLUDE 90!! FOR Z)
    for(int i = 0; i < len; i++){
        freqArray1[(int)inputString[i]]++;
    }

    // prompt for new string
    printf("%s", "ENTER NEW MESSAGE: ");
    fgets(inputString, MAX_CHAR, stdin);

    len = strlen(inputString);

    for(int i = 0; i < len; i++){
        freqArray2[(int)inputString[i]]++;
    }

    // value for printing here, compareFreq func passing both arrays
    int value = compareFreq(freqArray1, freqArray2);

    printf("\n%d", value);

    // Free memory, very important
    free(freqArray1);
    free(freqArray2);
    free(inputString);
    
    return 0;
}

// function prototypes

int *allocateString(int size){
    // calloc for sake of all 0s in memory instead of random addresses
    int *array = calloc(sizeof(char), size);

    //return ptr to access in main
    return array; 
}

int compareFreq(int *freq1, int *freq2){
    int count = 0;
    // only interested in 64 (A) -> (Z) (90)
    for(int i = 64; i<=90; i++){
        if(freq1[i] < freq2[i]){
            count += freq2[i] - freq1[i];
        }
    }
    return count;
}
