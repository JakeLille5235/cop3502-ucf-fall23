
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **pTriForm(int n);

void printTriangle(int **triangle, int n);

int main(void){
    
    int n = 0;
    scanf("%d", &n);


    int **pascalsTriangle = pTriForm(n);

    printTriangle(pascalsTriangle, n);

    return 0;
}

int **pTriForm(int n){
    int **tri = calloc(n, sizeof(int*)); //size of int ptr since a 2D array is an array of ptrs!!!

    //each row...

    /*
    tri[0] = allocate memory for THIS line
    tri[1] = allocate memory for THIS line
    tri[2] = allocate memory for THIS line
    tri[3] = allocate memory for THIS line
    etc...
    
    */

    for(int i = 0; i < n; i++){
        tri[i] = malloc((i+1)*sizeof(int));  // tri[i] only deals witb rows, starting position at each row
        tri[i][0] = 1;
        tri[i][i] = 1;
        for(int j = 1; j < i; j++){ // j start 1, 0 = 1 auto, columns always less than rows, esp with +1; 
            tri[i][j] = tri[i-1][j-1]+tri[i-1][j];

            /*
                  [0] [1][2]
               [0] 1
               [1] 1  1
               [2] 1  2  1

               etc.....
            */
        }
    }

    return tri; 
}


void printTriangle(int **triangle, int n){
    for(int i = 0; i < n; i ++){
        for(int j = 0; j <= i; j++ ){
            printf("%5d", triangle[i][j]);
        }
        puts("");
    }
}
