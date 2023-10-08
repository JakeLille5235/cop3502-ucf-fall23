/*
    Jake Lille
    CS1 P3 - wheretosit
    Guha, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables (as recommended) 
// max 10 people can attend, 19 chars each name MAX so 20 for null
int nMovie, antiPairs; // how many people
char attendNames[10][20];
char popCornNames[10][20]; // in the test-case all 10 have popcorn... make sure to check row if empty or contained
int antiSeat[10][2];
int popCornCounter = 0; // var to count how many people have popcorn, so we do not have to iterate 10 times through entire array everytime
int permCounter = 0; // how many permutations... 
int globalPermFlag = 0;


// functions... 
void printPerms(int perm[], int used[], int k, int n);
void print(int array[], int n);
int popCornCheck(int* perms);
int isValidSeating(int perms[], int index);
int isValid(int perms[], int n);
int checkConflict();
int checkPopList(char * name);
int findName(char* name);

int main(void){

    int counter = 0;
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

    counter = 0;
    
    while(counter < antiPairs){
        char tempName1[20];
        char tempName2[20];

        scanf("%s %s", tempName1, tempName2);
        // even odd = pair that can't sit together
        antiSeat[counter][0] = findName(tempName1);
        antiSeat[counter][1] = findName(tempName2); // stores the indicies of names in a 10 x 2 array
        counter++;
    }

    printPerms(perms, used, 0, nMovie);
    printf("\n%d", permCounter);


    // MAKE SURE TO CHECK IF EMPTY FOR NULL CHAR
   /* if(popCornNames[6][0] == '\0'){
        printf("%s", "HellO!");
    }
    */

   /*
   for(int i = 0; i < antiPairs; i++){
    printf("%d: %s %s\n", i, attendNames[antiSeat[i][0]], attendNames[antiSeat[i][1]]);
   } */


    return 0;
}

// return index of name in array
int findName(char* name){
    for(int i = 0; i < nMovie; i++){
        if(strcmp(name, attendNames[i]) == 0){
            return i;
        }
    }
    return -1;
}



int checkPopList(char * name){
    for(int i = 0; i < popCornCounter; i++){
        if(strcmp(name, popCornNames[i]) == 0){
            return 1;
        }
    }
    return 0; // false
}

int popCornCheck(int* perms){
    for(int i = 0; i < nMovie; i++){
        if(checkPopList(attendNames[perms[i]]) == 1){
            continue; // user has popcorn
        }
        if(checkPopList(attendNames[perms[i-1]]) == 1){
            continue;
        }
        if(checkPopList(attendNames[perms[i+1]]) == 1){
            continue;
        }
        return 0;
    }
    return 1;
}


int pairCheck(int perms[]){
    for(int i = 0; i < nMovie; i++){
        for(int j = 0; j < antiPairs*2; j++){
            if(strcmp(attendNames[perms[i]], attendNames[antiSeat[j][0]]) == 0){
                // match, find if issue...
                
                // no one on left, check only right
                if(i-1 < 0){
                    if(strcmp(attendNames[perms[i+1]], attendNames[antiSeat[j][1]]) == 0){
                        return 0;
                    }
                    continue;
                }
                if(i+1 == nMovie){
                    if(strcmp(attendNames[perms[i-1]], attendNames[antiSeat[j][1]]) == 0){
                        return 0;
                    }
                    continue;
                }
                if(strcmp(attendNames[perms[i-1]], attendNames[antiSeat[j][1]]) == 0 || strcmp(attendNames[perms[i+1]], attendNames[antiSeat[j][1]]) == 0){
                    return 0;
                }
                continue;
        }
        continue;
        }
    }
    return 1;
}


void print(int array[], int n) {
    int i;
    
    // ONLY PRINT IF PERMUTATION IS VALID
    if(popCornCheck(array) == 1 && pairCheck(array) == 1){
        for (i=0; i<n; i++){
        //validPopcorn(array[i], popCornCounter);
        //printf("%s ", attendNames[array[i]]);
    
        }
        permCounter++;
     printf("\n");
    }
}


void printPerms(int perm[], int used[], int k, int n) {

    // Base case.
    if (k == n){
        print(perm, n);
    }

    // Recursive case - fill in slot k.
    else {
        int i;

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


