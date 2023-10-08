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
char antiSeat[20][20];
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
    
    int tracker = 0;
    while(counter < antiPairs){
        char tempName1[20];
        char tempName2[20];

        scanf("%s %s", tempName1, tempName2);
        // even odd = pair that can't sit together

        
            strcpy(antiSeat[tracker], tempName1);
            tracker++;
            strcpy(antiSeat[tracker], tempName2);
            tracker++;
        
        counter++;
    }

    printPerms(perms, used, 0, nMovie);
    printf("\n%d", permCounter);


    // MAKE SURE TO CHECK IF EMPTY FOR NULL CHAR
   /* if(popCornNames[6][0] == '\0'){
        printf("%s", "HellO!");
    }
    */

    puts("");

    printf("\n%s", antiSeat[0]);
    printf("\n%s", antiSeat[1]);
    printf("\n%s", antiSeat[2]);
    printf("\n%s", antiSeat[3]);
    printf("\n%s", antiSeat[4]);
    printf("\n%s", antiSeat[5]);

    return 0;
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

int checkBanned(char * name){ // just checks if on list 
    for(int i = 0 ; i < antiPairs*2; i++){
        if(strcmp(name, antiSeat[i]) == 0){
            return i; // on list, return the index found. if even, the +1 index is their antipair, if odd the -1 index is their anti
        }
    }
    return -1;
}

int pairCheck(int *perms){
    for(int i = 0; i < nMovie; i++){
        if(i - 1 < 0){ // condition no one to left
            int index = checkBanned(attendNames[perms[i]]); 
            if(index != -1) { // there is a banned constriant...
                if(index % 2 == 0){ // even index
                    if(strcmp(attendNames[perms[i+1]], antiSeat[index+1]) == 0){
                        return 0; // constraint found
                    }
                    continue;
                }
                if(index % 2 != 0){ // odd index
                    if(strcmp(attendNames[perms[i+1]], antiSeat[index-1]) == 0){
                        return 0; // constraint found
                    }
                    continue;
                }
                continue;
            }
        }
        if(i+1 == nMovie){ // no one to right
            int index = checkBanned(attendNames[perms[i]]);
            if(index != -1){ //  banned constraint
                if(index % 2 == 0){ // even index
                    if(strcmp(attendNames[perms[i-1]], antiSeat[index+1]) == 0){
                        return 0; // constraint found
                    }
                    continue;
                }
                if(index % 2 != 0){ // odd index
                    if(strcmp(attendNames[perms[i-1]], antiSeat[index-1]) == 0){
                        return 0; // constraint found
                    }
                    continue;
                }
                continue;
            }
        } else { // left and right
            int index = checkBanned(attendNames[perms[i]]);
            if(index != -1){ //  banned constraint
                if(index % 2 == 0){ // even index
                    if(strcmp(attendNames[perms[i+1]], antiSeat[index+1]) == 0){
                        return 0; // constraint found
                    }
                    if(strcmp(attendNames[perms[i-1]], antiSeat[index+1]) == 0){
                        return 0; // constraint found
                    }
                    continue;
                }
                if(index % 2 != 0){ // odd index
                    if(strcmp(attendNames[perms[i-1]], antiSeat[index-1]) == 0){
                        return 0; // constraint found
                    }
                    if(strcmp(attendNames[perms[i+1]], antiSeat[index-1]) == 0){
                        return 0; // constraint found
                    }
                    continue;
                }
            }
        }
    }
    return 1;
}

/*int isValidSeating(int perms[], int index){
    for(int i = 0; i < antiPairs*2; i++){
        if(strcmp(attendNames[perms[index]], antiSeat[i]) == 0){ // if match
            if(i%2 == 0){ // even case meaning array+1 is the no sit
                if(index-1!=0 && strcmp(attendNames[perms[index-1]], antiSeat[i+1]) == 0 || index+1 == nMovie && strcmp(attendNames[perms[index+1]], antiSeat[i+1]) == 0 ){
                    return 0;
                } 
            } else{
                    if(index-1!=0 && strcmp(attendNames[perms[index-1]], antiSeat[i-1]) == 0 || index+1 == nMovie && strcmp(attendNames[perms[index+1]], antiSeat[i-1]) == 0){
                    return 0;
                }
        }
    }
}
return 1; 
}*/

void print(int array[], int n) {
    int i;
    
    // ONLY PRINT IF PERMUTATION IS VALID
    if(popCornCheck(array) == 1 && pairCheck(array) == 1){
        for (i=0; i<n; i++){
        //validPopcorn(array[i], popCornCounter);
        printf("%s ", attendNames[array[i]]);
    
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


