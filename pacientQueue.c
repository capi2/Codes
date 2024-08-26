#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//pacient's information
typedef struct typePacient{
    char name[30];
    unsigned age;
}typePacient;

//node with pacient's information
typedef struct typeNode{
    typePacient info;
    struct typeNode *next;
}typeNode;

//queue of pacients
typedef struct typeQueue{
    struct typeNode *first;
    struct typeNode *last;
    unsigned numPacients;
}typeQueue;

//creates and initializes the queue
void createQueue(typeQueue *q){
    q->first = NULL;
    q->last = NULL;
    q->numPacients = 0;
}

//creates node
typeNode *createNode(typePacient info){
    typeNode *aux = malloc(sizeof(typeNode));
    aux->info = info;
    aux->next = NULL;
    return aux;
}

//inserts at the first position of queue
void insertFirst(typeQueue *q, typePacient info){
    typeNode *aux = createNode(info);
    if(!q->first){
        aux->next = q->first;
        q->first = aux;
        q->last = aux;
    }else{
        aux->next = q->first;
        q->first = aux;
    }
    q->numPacients++;
}

//inserts at last position of queue
void insertLast(typeQueue *q, typePacient info){
    typeNode *aux = createNode(info);
    typeNode *tmp = q->last;
    if(!q->last){
        insertFirst(q, info);
    }else{
        tmp->next = aux;
        q->last = aux;
        q->numPacients++;
    }
}

//removes first position of queue
void removeFirst(typeQueue *q){
    typeNode *aux = q->first;
    if(!aux->next){
        q->first = NULL;
        q->last = NULL;
        q->numPacients = 0;
        free(aux);
    }else{
        q->first = aux->next;
        q->numPacients--;
        free(aux);
    }
}

//enqueues element
void enqueue(typeQueue *q, typePacient info){
    insertLast(q, info);
}

//dequeues element
void dequeue(typeQueue *q){
    removeFirst(q);
}

//shows every pacient's information in queue
void showQueue(typeQueue *q){
    typeNode *aux = q->first;
    printf("Number of pacients waiting... %u\n", q->numPacients);
    if(!aux){
        printf("Empty queue...\n");
    }else{
        while(aux){
            printf("-------Pacient----------\n");
            printf("Pacient's name: %s\n", aux->info.name);
            printf("Age: %u\n", aux->info.age);
            printf("------------------------\n");
            aux = aux->next;
        }
    }
}

//erases all information...
void deleteQueue(typeQueue *q){
    typeNode *aux = q->first;
    typeNode *tmp;
    q->first = NULL;
    q->last = NULL;
    q->numPacients = 0;
    while(aux){
        tmp = aux;
        free(tmp);
        aux = aux->next;
    }
}

int main(){
    typeQueue queue;
    createQueue(&queue);
    typePacient pacient;

    strcpy(pacient.name, "Anna Franz");
    pacient.age = 35;
    enqueue(&queue, pacient);

    strcpy(pacient.name, "Brown Carlito");
    pacient.age = 29;
    enqueue(&queue, pacient);

    strcpy(pacient.name, "Diana Lebron");
    pacient.age = 41;
    enqueue(&queue, pacient);

    strcpy(pacient.name, "Leonard Von Euman");
    pacient.age = 57;
    enqueue(&queue, pacient);

    showQueue(&queue);

    dequeue(&queue);

    showQueue(&queue);

    deleteQueue(&queue);

    showQueue(&queue);

    strcpy(pacient.name, "Ferdinand Thomas");
    pacient.age = 38;
    enqueue(&queue, pacient);

    showQueue(&queue);

    return 0;
}