/*
    JAKE LILLE
    SEPTEMBER 11TH, 2023
    COP 3502 P1 ASSIGNMENT - ASSIGNEDSEATING.C
*/

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


   int allocatedRows[MAXROWS+1] = {0}; //keep track of allocataed rows for freeing memory
   int aRCounter = 0;

   

    while(1){
        scanf("%6s", command);
        if(strcmp(command, "BUY") == 0){
            scanf("%d %d %d %50s", &row, &start, &end, name);
            //printf("%d %d %d %s", row, start, end, name);

            order* myOrder = make_order(start, end, name); 

            // check if lilleLounge[x] already allocated
            if(lilleLounge[row] == NULL){
                lilleLounge[row] = make_empty_row();

                // if new row being made, obviously empty so can skip call to can_add_order
                add_order(lilleLounge[row], myOrder);
                //update counter to keep track of what row #s to free at end of program
                allocatedRows[aRCounter] = row;
                aRCounter++;
                printf("%s", "SUCCESS\n");

            } else {
                if(can_add_order(lilleLounge[row] ,myOrder) == 1){
                    // row can be added! add order to list, etc.
                    add_order(lilleLounge[row], myOrder);
                    printf("%s", "SUCCESS\n");
                } else {
                    // row cannot be added, conflict, print failure
                    printf("%s", "FAILURE\n");
                    free_order(myOrder);
                }
            }

            //printf("%s", myOrder->name);


        }
        if(strcmp(command, "LOOKUP") == 0){
            scanf("%d %d", &row, &seat);
            //printf("%d %d", row, seat);
            printf("%s\n", get_owner(lilleLounge, row, seat));
        }
        if(strcmp(command, "QUIT") == 0){
            // free memory here, call approp functions
            for(int i = 0; i < aRCounter; i++){
                free_row(lilleLounge[allocatedRows[i]]);
            }

            free(lilleLounge);

            return 0;
        }
    
    }

    return 0;
}


// function defs

// memory alloc / setting up / init things
order* make_order(int start, int end, char* this_name){
    order* newOrder = calloc(1, sizeof(order));

    newOrder->s_seat = start;
    newOrder->e_seat = end;
    newOrder->name = strdup(this_name); // dynamically allocate and copy str

    return newOrder;
}

theaterrow* make_empty_row(){
    theaterrow* allocatedRow = calloc(1, sizeof(theaterrow));
    allocatedRow->list_orders = calloc(INITSIZE, sizeof(order*));
    allocatedRow->cur_size = 0;
    allocatedRow->max_size = INITSIZE;
    return allocatedRow; // make sure to assign this to the row index in main
}

int conflict(order* order1, order* order2){
   if (order2->s_seat <= order1->e_seat && order2->e_seat >= order1->s_seat){
        return 1; // there is a conflict
    }
    return 0; // no conflict
}


void add_order(theaterrow* this_row, order* this_order){

    if(this_row->cur_size == this_row->max_size){
        this_row->max_size *= 2; 
        this_row->list_orders = realloc(this_row->list_orders, this_row->max_size*sizeof(order*));
        if(this_row->list_orders == NULL){
           //return 0;
        }
        
    }
    this_row->list_orders[this_row->cur_size] = this_order;
    this_row->cur_size++;
    //return 1;
}

// if row already allocated, use this function
int can_add_order(theaterrow* this_row, order* this_order){
    for(int i = 0; i< this_row->cur_size; i++){
        if(conflict(this_order, this_row->list_orders[i]) == 1){
            return 0; // cannot be added!
        }
    }

    return 1; // can be added!
}

int contains(order* myorder, int seat_no) {
    if (seat_no >= myorder->s_seat && seat_no <= myorder->e_seat) {
        return 1; // seat_no is within the range
    } else {
        return 0; // seat_no is not within the range
    }
}

// thought having two of these functions redundant, but abiding by rubric/instructions here they are
// one accesses via arrowing down theater ptr, other operatoes by having row
char* get_owner(theaterrow** theater, int row, int seat_num){
    for(int i = 0; i < theater[row]->cur_size; i++){
        if(contains(theater[row]->list_orders[i], seat_num) == 1){
            return theater[row]->list_orders[i]->name;
            break;
        }
    }
    return NULL;
}

char* get_row_owner(theaterrow* this_row, int seat_num){
    for(int i = 0; i < this_row->cur_size; i++){
        if(contains(this_row->list_orders[i], seat_num) == 1){
            return this_row->list_orders[i]->name; 
            break;
        }
    }
    return "No one";
}


void free_order(order* this_order){
    free(this_order->name);
    free(this_order);
}

void free_row(theaterrow* this_row){
    for(int i=0; i<this_row->cur_size; i++){
        free_order(this_row->list_orders[i]); // USE free_order to account for string allocated for name
    }
    free(this_row->list_orders);
    free(this_row);
    // this function should cover all memory tied to row, make sure to free the entire theatre end of program
}