#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables (as recommended) 
// max 10 people can attend, 19 chars each name MAX so 20 for null
int nMovie; // how many people
char attendNames[10][20];
char popCornNames[10][20]; // in the test-case all 10 have popcorn... make sure to check row if empty or contained
int popCornCounter = 0; // var to count how many people have popcorn, so we do not have to iterate 10 times through entire array everytime
int permCounter = 0; // how many permutations... 


// functions... 
void printPerms(int perm[], int used[], int k, int n);
void print(int array[], int n);

int validPopcorn();
int checkConflict();

int main(void){

    int antiPairs, counter = 0;
    scanf("%d %d", &nMovie, &antiPairs);

    int used[nMovie];
    int perms[nMovie];
    for(int i = 0; i < nMovie; i++){
        used[i] = 0;
    }

    while(counter < nMovie){
        char tempName[20]; // for name
        int tempPop; // for popcorn correlating to name...
        
        scanf("%s %d", tempName, &tempPop);

        strcpy(attendNames[counter],tempName);

        if(tempPop ==  1){
            strcpy(popCornNames[popCornCounter], tempName);
            popCornCounter++;
        }


        counter++;
    }

    printPerms(perms, used, 0, nMovie);


    // MAKE SURE TO CHECK IF EMPTY FOR NULL CHAR
   /* if(popCornNames[6][0] == '\0'){
        printf("%s", "HellO!");
    }
    */
    return 0;
}



void print(int array[], int n) {
    int i;
    for (i=0; i<n; i++)
        printf("%s ", attendNames[array[i]]);
    printf("\n");
}


void printPerms(int perm[], int used[], int k, int n) {

    // Base case.
    if (k == n) print(perm, n);

    // Recursive case - fill in slot k.
    else {
        int i;

        // Only fill slot k with items that have yet to be used. If i hasn't been used,
        // put it in slot k and recursively print all permutations with these k+1 starting items.
        for (i=0; i<n; i++) {
            if (!used[i]) {
                used[i] = 1;
                perm[k] = i;
                printPerms(perm, used, k+1, n);
                used[i] = 0;
            }
        }
    }
}

/*void printPerms(char names[][20], int used[], int k, int n) {
    // Base case.
    if (k == n) {
        for (int i = 0; i < n; i++) {
            printf("%s ", names[used[i]]);
        }
        printf("\n");
    }
    // Recursive case - fill in slot k.
    else {
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                used[i] = 1;
                printPerms(names, used, k + 1, n);
                used[i] = 0;
            }
        }
    }
}*/