#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct typeCell{
    char bomb;
    char state;
}typeCell;

typedef struct typeMineField{
    typeCell **matrixCells;
}typeMineField;

typedef struct typeInput{
    int row;
    int column;
}typeInput;

typeMineField createMineField(int length, int height){
    typeMineField minefield;
    typeCell **matrix = malloc(sizeof(typeCell*)*length);
    if(!matrix){
        printf("[ERROR] MEMORY ALLOCATION ERROR WHEN CREATING NEW MATRIX!\n");
        exit(-1);
    }
    for(int k = 0; k < length; k++){
        matrix[k] = malloc(sizeof(typeCell)*height);
        if(!matrix[k]){
            printf("[ERROR] MEMORY ALLOCATION ERROR WHEN ALLOCATING COLUMNS OF MATRIX!\n");
            exit(-1);
        }
    }
    for(int i = 0; i < length; i++){
        for(int j = 0; j < height; j++){
            matrix[i][j].bomb = '0';
            matrix[i][j].state = '0';
        }
    }
    minefield.matrixCells = matrix;
    return minefield;
}

int randomNumber(int length, int height){
    return rand()%(length*height);
}

int isNumberOnList(int number, int *list, int limit){
    for(int i = 0; i < limit; i++){
        if(number == list[i]){
            return 1;
        }
    }
    return 0;
}

int *indexBombs(int numBombs, int length, int height){
    int *indexList = malloc(sizeof(int) * numBombs);
    if(!indexList){
        printf("[ERROR] PROBLEM WHILE ALLOCATING LIST OF INDEX OF BOMBS!\n");
        exit(-1);
    }
    for(int i = 0; i < numBombs; i++){
        int num = randomNumber(length, height);
        while(isNumberOnList(num, indexList, i)){
            num = randomNumber(length, height);
        }
        indexList[i] = num;
    }
    return indexList;
}

void insertionSort(int *list, int limit){
    int num;
    for(int i = 1; i < limit; i++){
        num = list[i];
        int j = i - 1;
        while(j >= 0 && list[j] > num){
            list[j+1] = list[j];
            j -= 1;
        }
        list[j+1] = num;
    }
}

void putbombs(typeMineField minefield, int numBombs, int length, int height){
    int *indexList = indexBombs(numBombs, length, height);
    insertionSort(indexList, numBombs);
    for(int i = 0; i < numBombs; i++){
        printf("%d\n", indexList[i]);
    }
    for(int i = 0; i < numBombs; i++){
        int count = 0;
        for(int j = 0; j < length; j++){
            for(int k = 0; k < height; k++){
                if(count == indexList[i]){
                    minefield.matrixCells[j][k].bomb = '1';
                } 
                count++;
            }
        }
    }
    free(indexList);
}

void showBombs(typeMineField mineField, int length, int height){
    printf("mostrando posicionamento das minas\n");
    for(int i = 0; i < length; i++){
        for(int j = 0; j < height; j++){
            printf("%c ", mineField.matrixCells[i][j].bomb);
        }
        printf("\n");
    }
}

int bombsAround(typeMineField mineField, int indexi, int indexj, int length, int height){
    int count = 0;
    for(int i = indexi-1; i <= indexi+1; i++){
        for(int j = indexj-1; j <= indexj+1; j++){
            if(i >= 0 && j >= 0 && i < length && j < height && mineField.matrixCells[i][j].bomb == '1'){
                count++;
            }
        }
    }
    return count;
}

void showMineField(typeMineField mineField, int length, int height){
    printf("mostrando campo minado\n");
    for(int i = 0; i < length; i++){
        for(int j = 0; j < height; j++){
            if(mineField.matrixCells[i][j].bomb != '1'){
                printf("%d ", bombsAround(mineField, i, j, length, height));
            }else{
                printf("b ");
            }
        }
        printf("\n");
    }
}

void showCoordinates(typeMineField mineField, int length, int height){
    printf("SHOWING COORDINATES AVAILABLE\n");
    for(int i = 0; i < length; i++){
        for(int j = 0; j < height; j++){
            typeCell cell = mineField.matrixCells[i][j];
            if(cell.state == '0'){
                printf("[%2d -%2d] ", i, j);
            }else if(cell.state == 'c'){
                printf("%8d ", bombsAround(mineField, i, j, length, height));
            }else if(cell.state == 'd'){
                printf("[DISARM] ");
            }
        }
        printf("\n");
    }
}

int selectDifficulty(){
    int diff;
    printf("Select level of difficult\n");
    printf("1 = Easy, 2 = Medium, 3 = Hard, 4 = Custom\n");
    while(scanf("%d%*c", &diff) != 1 || diff <= 0 || diff > 4){
        while (getchar() != '\n');
        printf("[ERROR] INVALID DIFFICULTY TRY AGAIN\n");
        printf("1 = Easy, 2 = Medium, 3 = Hard, 4 = Custom\n");
    }
    return diff;
}

typeInput readCoordinates(int row_chosen, int column_chosen, int length, int height){
    typeInput input;
    printf("Choose a row\n");
    while(scanf("%d%*c", &row_chosen) != 1 || row_chosen < 0 || row_chosen >= length){
        while (getchar() != '\n');
        printf("[ERROR] INVALID ROW TRY AGAIN\n");
    }

    printf("Choose a column\n");
    while(scanf("%d%*c", &column_chosen) != 1 || column_chosen < 0 || column_chosen >= height){
        while (getchar() != '\n');
        printf("[ERROR] INVALID COLUMN TRY AGAIN\n");
    }

    input.row = row_chosen;
    input.column = column_chosen;
    return input;
}

void deleteMineField(typeMineField mineField, int length){
    for(int i = 0; i < length; i++){
        free(mineField.matrixCells[i]);
    }
    free(mineField.matrixCells);
}

void game(){
    int length;
    int height;
    int bombs;

    int difficulty = selectDifficulty();
    if(difficulty == 1){
        length = 3;
        height = 3;
        bombs = 3;
    }else if(difficulty == 2){
        length = 5;
        height = 5;
        bombs = 7;
    }else if(difficulty == 3){
        length = 7;
        height = 8;
        bombs = 15;
    }else if(difficulty == 4){
        printf("Type length of board ");
        while(scanf("%d%*c", &length) != 1){
            while (getchar() != '\n');
            printf("[ERROR] INVALID LENGTH TRY AGAIN\n");
        }

        printf("Type heigth of board ");
        while(scanf("%d%*c", &height) != 1){
            while (getchar() != '\n');
            printf("[ERROR] INVALID HEIGHT TRY AGAIN\n");
        }

        while(length*height == 1){
            printf("[WARNING] BOARD WITH 1 SINGLE CELL!\n");
            printf("Type length of board ");
            while(scanf("%d%*c", &length) != 1){
                while (getchar() != '\n');
                printf("[ERROR] INVALID LENGTH TRY AGAIN\n");
            }
            
            printf("Type heigth of board ");
            while(scanf("%d%*c", &height) != 1){
                while (getchar() != '\n');
                printf("[ERROR] INVALID HEIGHT TRY AGAIN\n");
            }
        }

        printf("How many bombs do you want? ");
        while(scanf("%d%*c", &bombs) != 1){
            while (getchar() != '\n');
            printf("[ERROR] INVALID NUMBER OF BOMBS TRY AGAIN\n");
        }

        while(bombs >= length*height || bombs <= 0){
            printf("How many bombs do you want? ");
            while(scanf("%d%*c", &bombs) != 1){
                while (getchar() != '\n');
                printf("[ERROR] INVALID NUMBER OF BOMBS TRY AGAIN\n");
            }
        }
    }

    typeMineField minefield = createMineField(length, height);
    putbombs(minefield, bombs, length, height);

    char gameover = '0';
    int row_chosen;
    int column_chosen;
    int command;
    int defuses = bombs;
    int cellsLefttoChoose = length*height - bombs;
    char alertMessage[70] = "";
    printf("GAME BEGIN\n");

    while(gameover == '0'){
        system("clear");
        printf("%s", alertMessage);
        showCoordinates(minefield, length, height);
        printf("WHAT YOU WANT TO DO?\n");
        printf("OPTIONS: 1 = REVEAL A CELL; 2 = DISARM A CELL; 3 = QUIT ");
        while(scanf("%d%*c", &command) != 1 || command < 1 || command > 3){
            while (getchar() != '\n');
            printf("[ERROR] INVALID COMMAND TRY AGAIN\n");
            printf("OPTIONS: 1 = REVEAL A CELL; 2 = DISARM A CELL; 3 = QUIT ");
        }

        if(command == 1){
            printf("CHOOSE A CELL TO REVEAL\n");
            typeInput input = readCoordinates(row_chosen, column_chosen, length, height);
            typeCell cell = minefield.matrixCells[input.row][input.column];
            if(cell.state == 'd'){
                strcpy(alertMessage, "THIS COORDINATE WAS DISARMED! UNDO DISARMING FIRST TO REVEAL CELL!\n");
            }else if(cell.bomb == '1'){
                printf("THE BOMB EXPLODED\n");
                gameover = 1;
            }else if(cell.state == 'c'){
                strcpy(alertMessage, "THIS COORDINATE WAS ALREADY CHOSEN!\n");
            }else if(cell.state == '0'){
                strcpy(alertMessage, "CELL REVEALED!\n");
                minefield.matrixCells[input.row][input.column].state = 'c';
                cellsLefttoChoose--;
            }
        }else if(command == 2){
            printf("CHOOSE A CELL TO DISARM IF CELL IS ALREADY DISARMED YOU UNDO IT AND RECEIVE ONE DEFUSE BACK!\n");
            typeInput input = readCoordinates(row_chosen, column_chosen, length, height);
            typeCell cell = minefield.matrixCells[input.row][input.column];
            if(cell.state == 'c'){
                strcpy(alertMessage, "CANT DISARM A COORDINATE THAT WAS ALREADY CHOSEN!\n");
            }else{
                if(cell.state == '0'){
                    strcpy(alertMessage, "CELL DISARMED!\n");
                    minefield.matrixCells[input.row][input.column].state = 'd';
                    defuses--;
                    if(cell.bomb == '1'){
                        bombs--;
                    }
                }else{
                    strcpy(alertMessage, "DISARMING REVERSED!\n");
                    minefield.matrixCells[input.row][input.column].state = '0';
                    defuses++;
                    if(cell.bomb == '1'){
                        bombs++;
                    }
                }
            }
        }else if(command == 3){
            gameover = 1;
        }
        if(cellsLefttoChoose == 0 && bombs == 0){
            showCoordinates(minefield, length, height);
            printf("CONGRATULATIONS ALL BOMBS DISARMED\n");
            gameover = 1;
        }
    }
    printf("GAME OVER\n");
    deleteMineField(minefield,length);
}

int main(){
    srand(time(NULL));
    game();
}