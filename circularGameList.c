#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//player's name and score
typedef struct player{
    char name[30];
    unsigned lives;
}player;

//node contaning player's information
typedef struct typeNode{
    player info;
    struct typeNode *next;
}typeNode;

//circular list of players
typedef struct typeCircularList{
    struct typeNode *start;
    struct typeNode *end;
    unsigned numPlayers;
}typeCircularList;

//creates and initializes circular list
void createCircularList(typeCircularList *cl){
    cl->start = NULL;
    cl->end = NULL;
    cl->numPlayers = 0;
}

//creates and returns a simple node
typeNode *createNode(player info){
    typeNode *aux = malloc(sizeof(typeNode));
    aux->info = info;
    aux->next = NULL;
    return aux;
}

//inserts at the first position of list
void insertFirst(typeCircularList *cl, player info){
    typeNode *aux = createNode(info);
    if(!cl->start){
        cl->start = aux;
        cl->end = aux;
        aux->next = aux;
    }else{
        aux->next = cl->start;
        cl->start = aux;
        cl->end->next = aux;
    }
    cl->numPlayers++;
}

//inserts at last position of list
void insertLast(typeCircularList *cl, player info){
    typeNode *aux = createNode(info);
    if(!cl->start){
        insertFirst(cl, info);
    }else{
        cl->end->next = aux;
        aux->next = cl->start;
        cl->end = aux;
        cl->numPlayers++;
    }
}

//removes first element of list
void removeFirst(typeCircularList *cl){
    typeNode *aux = cl->start;
    typeNode *tmp;
    if(!aux){
        printf("Nothing to remove...\n");
    }else{
        if(cl->numPlayers == 1){
            tmp = aux;
            free(tmp);
            cl->start = NULL;
            cl->end = NULL;
            cl->numPlayers = 0;
        }else{
            cl->start = aux->next;
            cl->end->next = aux->next;
            tmp = aux;
            free(tmp);
            cl->numPlayers--;
        }
    }
}

//removes player from list by given name
void removePlayer(typeCircularList *cl, char *name){
    typeNode *aux = cl->start;
    typeNode *tmp;
    if(!aux){
        printf("Nothing to remove...\n");
    }else{
        if(!strcmp(aux->info.name, name)){
            removeFirst(cl);
        }else{
            tmp = aux;
            aux = aux->next;
            while(aux != cl->start){
                if(aux == cl->end && !strcmp(aux->info.name,name)){
                    tmp->next = aux->next;
                    cl->end = tmp;
                    tmp = aux;
                    free(tmp);
                    cl->numPlayers--;
                    break;
                }else{
                    if(!strcmp(aux->info.name,name)){
                        tmp->next = aux->next;
                        tmp = aux;
                        free(tmp);
                        cl->numPlayers--;
                        break;
                    }else{
                        tmp = aux;
                        aux = aux->next;
                    }
                }
            }
        }
    }
}

//shows entire list
void showCircularList(typeCircularList *cl){
    typeNode *aux = cl->start;
    printf("Number of players: %u\n", cl->numPlayers);
    if(!aux){
        printf("Empty circular list...\n");
    }else{
        printf("--------------------------------\n");
        printf("Player's name: %s\n", aux->info.name);
        printf("Remaining lives: %u\n", aux->info.lives);
        printf("--------------------------------\n");
        aux = aux->next;
    }while(aux != cl->start){
        printf("--------------------------------\n");
        printf("Player's name: %s\n", aux->info.name);
        printf("Remaining lives: %u\n", aux->info.lives);
        printf("--------------------------------\n");
        aux = aux->next;
    }
}

//deletes the entire list
void deleteCircularList(typeCircularList *cl){
    typeNode *aux = cl->start;
    typeNode *tmp;
    aux = aux->next;
    while(aux != cl->start){
        tmp = aux;
        free(tmp);
        aux = aux->next;
    }
    tmp = aux;
    free(tmp);
    cl->start = NULL;
    cl->end = NULL;
    cl->numPlayers = 0;
}

//returns a random number
unsigned randomNumber(){
    return rand()%5;
}

//begin the random number game
void beginGame(typeCircularList *cl){
    typeNode *aux = cl->start;
    int num = 1;
    unsigned rndNumb;
    unsigned guess;
    unsigned winner = 0;
    printf("Welcome to Guess The Number Game!\n");
    printf("Rules are simple, guess a random number!\n");
    printf("Each incorrect guess reduces your lives by 1!\n");
    printf("If a player's lives reaches 0, they are eliminated!\n");
    printf("Last one standing is the ultimate winner!\n");
    while(num != -1){
        if(winner){
            printf("Game over\n");
            printf("And the winner is...\n");
            printf("%s !!!!\n", aux->info.name);
            break;
        }
        printf("Now it's %s turn!!!\n", aux->info.name);
        printf("What are you going to do?\n");
        printf("1 - Show scores; 2 - Guess the number; -1 - Close game\n");
        scanf("%d", &num);
        if(num == 1){
            printf("Current results are shown below...\n");
            showCircularList(cl);
        }else if(num == 2){
            rndNumb = randomNumber();
            printf("Well then...guess the number!\n");
            scanf("%u%*c", &guess);
            if(rndNumb == guess){
                printf("Well done...correct guess!!!\n");
                aux = aux->next;
            }else{
                printf("Wrong number...\n");
                printf("%s you lost a live...\n", aux->info.name);
                aux->info.lives--;
                if(!aux->info.lives){
                    printf("%s you lost all lives...\n", aux->info.name);
                    removePlayer(cl, aux->info.name);
                    printf("Good luck next time...\n");
                    if(cl->numPlayers == 1){
                        winner = 1;
                    }
                }
                aux = aux->next;
            }
        }else if(num == -1){
            printf("Game over\n");
            printf("Final results...\n");
            showCircularList(cl);
        }else{
            printf("Invalid option, please inform a valid number\n");
        }
    }
}

int main(){
    srand(time(NULL));
    typeCircularList circularList;
    createCircularList(&circularList);
    player pl;

    strcpy(pl.name, "Thomas Guzgnaiver");
    pl.lives = 1;
    insertLast(&circularList, pl);

    strcpy(pl.name, "Hortesia Ximenez");
    pl.lives = 1;
    insertFirst(&circularList, pl);

    strcpy(pl.name, "Paul Klutz");
    pl.lives = 1;
    insertLast(&circularList, pl);

    strcpy(pl.name, "Amanda Tachibana");
    pl.lives = 1;
    insertFirst(&circularList, pl);

    beginGame(&circularList);

    return 0;
}