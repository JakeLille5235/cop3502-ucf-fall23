#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITSIZE 10
#define MAXLEN 50
#define MAXROWS 100000

// for oders
typedef struct order {
    int s_seat;
    int e_seat;
    char* name;
}   order;

// manage single row (most important/used)
typedef struct theaterrow {
    order** list_orders;
    int max_size;
    int cur_size;
} theaterrow;


// function prototypes
order* make_order(int start, int end, char* this_name);

theaterrow* make_empty_row();

int conflict(order* order1, order* order2);

int can_add_order(theaterrow* this_row, order* this_order);

void add_order(theaterrow* this_row, order* this_order);

char* get_owner(theaterrow** theater, int row, int seat_num);

char* get_row_owner(theaterrow* this_row, int seat_num);

int contains(order* myorder, int seat_no);

void free_order(order* this_order);

void free_row(theaterrow* this_row);


int main(void){

    theaterrow** amc_= calloc(MAXROWS+1, sizeof(theaterrow*)); // !!! make sure to free this one in main @ end

    char command[7]; // 'LOOKUP' = longest 6 + null
    int row, start, end, seat; // 1 - 100,000
    char name[50]; // '

    while(1){
        scanf("%6s", command);
        if(strcmp(command, "BUY") == 0){
            scanf("%d %d %d %49s", &row, &start, &end, name);
            printf("%d %d %d %s", row, start, end, name);
        }
        if(strcmp(command, "LOOKUP") == 0){
            scanf("%d %d", &row, &seat);
            printf("%d %d", row, seat);
        }
        if(strcmp(command, "QUIT") == 0){
            // free memory here, call approp functions

            return 0;
        }
    
    }

    return 0;
}