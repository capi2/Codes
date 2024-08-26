#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//description of what needs to be done
typedef struct toDo{
    char description[50];
}toDo;

//node containing description of what to do
typedef struct typeNode{
    toDo info;
    struct typeNode *next;
}typeNode;

//stack of things to do
typedef struct typeStack{
    typeNode *first;
    typeNode *last;
    unsigned numThingsToDo;
}typeStack;

//creates and initializes the stack
void createStack(typeStack *s){
    s->first = NULL;
    s->last = NULL;
    s->numThingsToDo = 0;
}

//creates node
typeNode *createNode(toDo info){
    typeNode *aux = malloc(sizeof(typeNode));
    aux->info = info;
    aux->next = NULL;
    return aux;
}

//inserts at the first position of stack
void insertFirst(typeStack *s, toDo info){
    typeNode *aux = createNode(info);
    if(!s->first){
        s->first = aux;
        s->last = aux;
    }else{
        aux->next = s->first;
        s->first = aux;
    }
    s->numThingsToDo++;
}

//inserts at the last position of stack
void insertLast(typeStack *s, toDo info){
    typeNode *aux = createNode(info);
    typeNode *tmp = s->last;
    if(!s->last){
        insertFirst(s,info);
    }else{
        tmp->next = aux;
        s->last = aux;
        s->numThingsToDo++;
    }
}

//removes last element of stack
void removeLast(typeStack *s){
    typeNode *aux = s->first;
    typeNode *tmp;
    if(!aux->next){
        s->first = NULL;
        s->last = NULL;
        s->numThingsToDo = 0;
        free(aux);
    }else{
        tmp = aux;
        aux = aux->next;
        while(aux->next){
            tmp = aux;
            aux = aux->next;
        }
        tmp->next = NULL;
        s->last = tmp;
        s->numThingsToDo--;
        free(aux);
    }
}

//pushes element
void push(typeStack *s, toDo info){
    insertLast(s, info);
}

//pops element
void pop(typeStack *s){
    removeLast(s);
}

//shows the entire stack
void showStack(typeStack *s){
    typeNode *aux = s->first;
    printf("Things to do.... %u\n",s->numThingsToDo);
    if(!aux){
        printf("Nothing to do...\n");
    }else{
        while(aux){
            printf("Description: %s\n", aux->info.description);
            aux = aux->next;
        }
    }
}

int main(){
    typeStack stack;
    createStack(&stack);
    toDo todo;

    strcpy(todo.description, "Pay the bills");
    push(&stack, todo);

    showStack(&stack);

    pop(&stack);

    showStack(&stack);

    strcpy(todo.description, "Wash the car");
    push(&stack, todo);

    strcpy(todo.description, "Buy food");
    push(&stack, todo);

    showStack(&stack);

    pop(&stack);

    showStack(&stack);

    strcpy(todo.description, "Study for English Exam");
    push(&stack, todo);

    showStack(&stack);

    pop(&stack);

    showStack(&stack);
    
}