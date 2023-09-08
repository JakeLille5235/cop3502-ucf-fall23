#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITSIZE 10
#define MAXLEN 51 // safety reasons
#define MAXROWS 100001 // safety reasons

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

    // create 2D array of struct ptrs...
    /*
        ptrToStructRow1 = S1 S2 S3 S4 S5 etc.
        ptrToStructRow2 = S1 S2 S3 S4 S5 etc.
    
    */
    theaterrow** lilleLounge = calloc(MAXROWS+1, sizeof(theaterrow*)); // !!! make sure to free this one in main @ end


    char command[7]; // 'LOOKUP' = longest 6 + null
    int row, start, end, seat; // 1 - 100,000
    char name[50]; // longest name including null can be 50 chars

    while(1){
        scanf("%6s", command);
        if(strcmp(command, "BUY") == 0){
            scanf("%d %d %d %49s", &row, &start, &end, name);
            //printf("%d %d %d %s", row, start, end, name);

            order* myOrder = make_order(start, end, name);

            // check if lilleLounge[x] already allocated
            if(lilleLounge[row] == NULL){
                make_empty_row();
            }

            printf("%s", myOrder->name);


        }
        if(strcmp(command, "LOOKUP") == 0){
            scanf("%d %d", &row, &seat);
            //printf("%d %d", row, seat);
        }
        if(strcmp(command, "QUIT") == 0){
            // free memory here, call approp functions

            return 0;
        }
    
    }

    return 0;
}

order* make_order(int start, int end, char* this_name){
    order* newOrder = calloc(1, sizeof(order));

    newOrder->s_seat = start;
    newOrder->e_seat = end;
    newOrder->name = strdup(this_name); // dynamically allocate and copy str

    return newOrder;
}

theaterrow* make_empty_row(){
    theaterrow* allocatedRow = calloc(INITSIZE, sizeof(theaterrow));
    allocatedRow->list_orders = calloc(INITSIZE, sizeof(order));
    allocatedRow->cur_size = 0;
    allocatedRow->max_size = 10;
    return allocatedRow;
}


void add_order(theaterrow* this_row, order* this_order){

    if(this_row->cur_size >= this_row->max_size){
        realloc(this_row->list_orders, (this_row->max_size*2)*sizeof(order));
    }
    this_row->list_orders[this_row->cur_size] = this_order;
    this_row->cur_size++;
}


void free_order(order* this_order){
    free(this_order->name);
    free(this_order);
}

void free_row(theaterrow* this_row){

}