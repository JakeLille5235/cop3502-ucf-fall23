/*
Jake Lille
September 5th, 2023
Recitation #1 Kattis
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 21 // max 20 + null char


void reverseString(char *str);


int main(void){
    //declare vars
    int nCase = 0;
    int row = 0;
    int column = 0;
    char stringLine[MAX_STRING] = "";
    

    // test case #
    scanf("%d", &nCase);
    // row tracker used for iteration later, allows for looping correctly in allStrings array
    int *rowTracker = malloc((1+nCase)*sizeof(int));
    rowTracker[0] = 0;

    //count for how many rows & columns
    int count = 0;
    char **allStrings = malloc(20*sizeof(char*));
    
    // loop for # of cases
    for(int i = 0; i<nCase; i++){
        scanf("%d %d", &row, &column);
        allStrings = realloc(allStrings, (count+row)*sizeof(char*));
            for(int i = 0; i+count < row+count; i++){
                allStrings[i+count] = malloc((column+1)*sizeof(char));
                //allStrings[i] = realloc(allStrings[i],column*sizeof(char)+1);
                scanf("%s", stringLine);
                strcpy(allStrings[i+count], stringLine);
            }
       count += row; 
       rowTracker[i+1] = count;
    }

    //decrement to go back and correcly 'mirror' the image
    for(int i = 0; i < nCase; i++){
        printf("Test %d\n", i+1);
        for(int j = rowTracker[i+1]-1; j >= rowTracker[i]; j--){
            reverseString(allStrings[j]);
            printf("%s", allStrings[j]);
            puts("");
        }
    } 
    
    //printf("%s", allStrings[2]);

    // free all memory!
    free(rowTracker);
    // individual strings first so they aren't lost in memory
    for(int i = 0; i < count; i++){
        free(allStrings[i]);
    }
    free(allStrings);

    return 0;
}

// reverse string function: mirrow is essentially reversed string, printed backwards
void reverseString(char *str){
    int length = strlen(str);
    int i,j;
    char temp;

    for(i = 0, j = length - 1; i<j; i++, j--){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}