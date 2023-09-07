#include <stdio.h>
#include <stdlib.h>

// Linked Lists template...

/*
    |DATA|LINK|      data being a data type, link being a pointer to next node or NULL
        NODE 
*/

// ie template in form of struct...

struct node {
    int data;
    struct node *link; //ptr to another node, which MUST be another struct
    // a 'self referential structure'
};


int main(void){
    struct node *head = NULL;
    head = (struct node *)malloc(sizeof(struct node)); // store address of first node or BASE ADDRESS

    head->data = 45;
    head->link = NULL;

    struct node *current = malloc(sizeof(struct node));
    current->data = 98;
    current->link = NULL;
    head->link = current;

    current = malloc(sizeof(struct node));
    current->data = 3;
    current->link = current;
    head->link->link = current;

    printf("%d", head->data);

    return 0;
}