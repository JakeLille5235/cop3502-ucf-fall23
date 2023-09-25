/*
    Jake Lille
    CS1 Guha, P2 Assignment "MoveLine"
    September 25th, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 51
#define ASCII_FIX 65 // to subtract to find p value (0<=p<=25)
#define TOTAL_QUEUES 12
#define EMPTY -1


// structs for lists, queue and customer
typedef struct customer {
    char* name;
    int ticketQty;
    int queueNum; // INDEX + 1 for 1-12 proper
    long long timeArrived; 
} customer;

typedef struct node {
    customer * customerData; // store the customer data in a struct called customer, ptr to the struct the "node data"
    struct node* next;
} node;

typedef struct queue {
    struct node* front;
    struct node* back;
} queue;


// prototypes

/*
    sketch for functions we will need

    1. createCustomer (dynamically allocate memory (malloc sizeof customer struct)), determine the queue position
    2. enqueue
    3. dequeue
    4. isEmpty (check if queues empty for assignment)
    5. front (return the front of a queue)
    6. queueSize (to determine which queues to assign)

*/

customer * createCustomer(char name[MAX_NAME], int tickets, long long timeArrived);

int queueSize(queue q);



int main(void){


    // Theatre has 12 queues (given) NUM 1-12!!! make sure to accomodate for index notation
    queue queues[TOTAL_QUEUES];

    int customerNumber, boothNumber, count = 0;

    scanf("%d %d", &customerNumber, &boothNumber);

    while(count < customerNumber){
        

        count++;
    }

    return 0;
}


customer * createCustomer(char name[MAX_NAME], int tickets, long long timeArrived){
    customer* newCustomer = malloc(sizeof(customer));
    newCustomer->name = strdup(name); // dynamically allocate space for string name
}

int queueSize(queue q){
    int size = 0;
    node* current =  q.front;

    while(current != NULL){
        size++;
        current = current->next;
    }

    return size;

}



