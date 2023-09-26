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
#define EMPTY 1 // 0 if not empty


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
    int size; // THIS is how we will determine the size, reduce O(n) time so we don't have to iterate every list etc...
} queue;


// prototypes

/*
    sketch for functions we will need

    1. createCustomer (dynamically allocate memory (malloc sizeof customer struct)), determine the queue position
    2. enqueue
    3. dequeue (make sure to free memory)
    4. isEmpty (check if queues empty for assignment)
    5. PEEK (return the front of a queue WITHOUT DEQUEUEING)
    6. queueSize (to determine which queues to assign)

    freeMemory

*/


int enqueue(queue * qPtr, customer * cPtr);
int dequeue(queue * qPtr);
int isEmpty(queue * qPtr);
int peek(queue * qPtr);

//int calcBooth(int nonEmptyQueues);

void assignToBooth();

customer * createCustomer(char name[MAX_NAME], int tickets, long long timeArrived);

// int queueSize(queue q);



int main(void){


    // Theatre has 12 queues (given) NUM 1-12!!! make sure to accomodate for index notation
    queue * queues[TOTAL_QUEUES];
    memset(queues, 0, sizeof(queue*) * TOTAL_QUEUES); // set queue elements to null

    int customerNumber, boothNumber, count = 0;

    scanf("%d %d", &customerNumber, &boothNumber);

    while(count < customerNumber){

        char name[MAX_NAME];
        int tickets = 0;
        long long timeArrived = 0;

        scanf("%50s %d %lld", name, &tickets, &timeArrived);

        customer* newCustomer = createCustomer(name, tickets, timeArrived);

        int q = 1; //calculate q here;

        // allocate queue memory
        if(queues[q] == NULL){
           queues[q] = malloc(sizeof(queue));
        }

        enqueue(queues[q], newCustomer);

        printf("%s %d", queues[q]->front->customerData->name, queues[q]->front->customerData->ticketQty);

        count++;
    }

    return 0;
}


customer * createCustomer(char name[MAX_NAME], int tickets, long long timeArrived){
    customer* newCustomer = malloc(sizeof(customer));

    newCustomer->name = strdup(name); // dynamically allocate space for string name
    newCustomer->ticketQty = tickets;
    newCustomer->timeArrived = timeArrived;

    return newCustomer;

}

int enqueue(queue * qPtr, customer * cPtr){
    node * temp;

    // allocate size for the node itself...
    temp = malloc(sizeof(node));

    // if memory allocation was SUCCESS...
    if(temp != NULL){
        // set customerData to ptr of customer (from createCustomer)
        temp->customerData = cPtr;
        // set next to NULL as this enqueues a new value with no next yet
        temp->next = NULL;

        // if back is NOT NULL (ie. not a new queue)
        if(qPtr->back != NULL){
            // link the previous node to this node
            qPtr->back->next = temp;
        }
        // set new back of queue to current node
        qPtr->back = temp;

        if(qPtr->front == NULL){
            qPtr->front = temp;
        }

        qPtr->size++;

        return 1; // means success
    }

    else return 0; // failure
}

int dequeue(queue * qPtr){
    node* temp;
    int retval;

    // check if empty
    if(qPtr->front == NULL){
        return -1; // returns -1 IF EMPTY (can't have -1 tx but in weird case we have 0...)
    }
    
    // store front value to return
    // THIS WILL BE THE CHECKOIT TIME
    retval = qPtr->front->customerData->timeArrived; // CALL CHECKOUT CALCULATION FUNCITON HERE

    // temp ptr for free memory usage
    temp = qPtr->front;

    // set new front for next dequeue and update queue
    qPtr->front = qPtr->front->next;

    // check if this was last node, making queue empty...
    if(qPtr->front == NULL){
        qPtr->back = NULL;
    }

    // free memory
    free(temp);

    //return retval;
    return 1;
}


/*
int calcQueue(customer* newCustomer,){
    int p = newCustomer->name[0]-ASCII_FIX; // ASCII math to find numeric value of letter
    
}

int calcBooth(queue queues, int booths){
    // call func to find queues non-empty


}
*/


/*
int queueSize(queue q){
    int size = 0;
    node* current =  q.front;

    while(current != NULL){
        size++;
        current = current->next;
    }

    return size;

}

*/