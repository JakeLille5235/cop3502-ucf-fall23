#include <stdio.h>
#include <stdlib.h>


// max # of chars that can be read as input (including terminating null char)
#define MAX_CHAR 100000

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

int main(void){


    return 0;
}