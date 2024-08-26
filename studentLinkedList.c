#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//student's information
typedef struct typeStudent{
    char studentName[30];
    unsigned age;
    char course[30];
}typeStudent;

//node containing student's info and a pointer to next node
typedef struct typeNode{
    typeStudent info;
    struct typeNode *next;
}typeNode;

//linked list with pointer to first and last element of list and a variable that stores the number of students within list
typedef struct typeList{
    struct typeNode *first;
    struct typeNode *last;
    unsigned studentNumber;
}typeList;

//creates the list
void createList(typeList *l){
    l->first = NULL;
    l->last = NULL;
    l->studentNumber = 0;
}

//creates and returns a simple node with student's information
typeNode* createNode(typeStudent info){
    typeNode *aux = malloc(sizeof(typeNode));
    aux->info = info;
    aux->next = NULL;
    return aux;
}

//inserts at the beginning position of the list
void insertBeginning(typeList *l, typeStudent info){
    typeNode *aux = createNode(info);
    if(!l->first){
        l->first = aux;
        l->last = aux;
    }else{
        aux->next = l->first;
        l->first = aux;
    }
    l->studentNumber++;
}

//inserts at the last position of the list
void insertLast(typeList *l, typeStudent info){
    typeNode *aux = createNode(info);
    typeNode *tmp = l->last;
    if(!l->first){
        l->first = aux;
        l->last = aux;
    }else{
        tmp->next = aux;
        l->last = aux;
    }
    l->studentNumber++;
}

//searches for element on list by a given name
typeNode* searchElement(typeList *l, char *name){
    typeNode *aux = l->first;
    while(aux){
        if(!strcmp(aux->info.studentName, name)){
            return aux;
        }else{
            aux = aux->next;
        }
    }
    return NULL;
}

//searches for element on list and shows the data of it
void searchByName(typeList *l, char* name){
    typeNode *aux = searchElement(l, name);
    if(aux){
        printf("Element found! Showing data...\n");
        printf("Name: %s\n", aux->info.studentName);
        printf("Age: %u years\n", aux->info.age);
        printf("Course: %s\n", aux->info.course);
        printf("##################################################\n");
    }else{
        printf("Element wasn't found on list...\n");
    }
}

//searches for a element using oldName and replaces it for newName
void modifyName(typeList *l, char* oldName, char* newName){
    typeNode *aux = searchElement(l, oldName);
    if(aux){
        printf("%s found! Modifying name...\n", oldName);
        strcpy(aux->info.studentName, newName);
    }else{
        printf("No element was found to modify name...\n");
    }
}

//searches for a student using name and replaces old age for newAge
void modifyAge(typeList *l, char* name, unsigned newAge){
    typeNode *aux = searchElement(l, name);
    if(aux){
        printf("%s found! Modifying age...\n", name);
        aux->info.age = newAge;
    }else{
        printf("No element was found to modify age...\n");
    }
}

//searches for a student using name and replaces old course for newCourse
void modifyCourse(typeList *l, char* name, char* newCourse){
    typeNode *aux = searchElement(l, name);
    if(aux){
        printf("%s found! Modifying course...\n", name);
        strcpy(aux->info.course, newCourse);
    }else{
        printf("No element was found to modify course...\n");
    }
}

//removes first element of list
void removeFirst(typeList *l){
    typeNode *aux = l->first;
    if(l->studentNumber == 1){
        l->first = NULL;
        l->last = NULL;
        free(aux);
    }else{
        l->first = aux->next;
    }
}

//removes any element of list by given name
int removeElement(typeList *l, char* name){
    typeNode *aux = l->first;
    typeNode *tmp;
    if(!strcmp(aux->info.studentName, name)){
        removeFirst(l);
        l->studentNumber--;
        return 1;
    }else{
        tmp = aux;
        aux = aux->next;
        while(aux){
            if(!strcmp(aux->info.studentName, name)){{
                if(!aux->next){
                    l->last = tmp;
                    tmp->next = NULL;
                    free(aux);
                    l->studentNumber--;
                    return 1;
                }else{
                    tmp->next = aux->next;
                    free(aux);
                    l->studentNumber--;
                    return 1;
                }
            }}else{
                tmp = aux;
                aux = aux->next;
            }
        }
    }
    return 0;
}

//tries to remove element of list and returns a message if it was successful or not
void removeByName(typeList *l, char *name){
    if(removeElement(l, name)){
        printf("%s was found and succesfully removed!!!\n", name);
    }else{
        printf("No element found for removal...\n");
    }
}

//inserts student by fiding its right position on list
int orderedInsertionByName(typeList *l, typeStudent info){
    typeNode *aux = createNode(info);
    typeNode *tmp = l->first;
    typeNode *tmp2;
    if(!tmp){
        l->first = aux;
        l->last = aux;
        l->studentNumber++;
        return 1;
    }else{
        if(strcmp(info.studentName, tmp->info.studentName) < 0){
            aux->next = l->first;
            l->first = aux;
            l->studentNumber++;
            return 1;
        }else{
            tmp2 = tmp;
            tmp = tmp->next;
            while(tmp){
                if(strcmp(info.studentName, tmp->info.studentName) < 0){
                    aux->next = tmp;
                    tmp2->next = aux;
                    l->studentNumber++;
                    return 1;
                }else{
                    tmp2 = tmp;
                    tmp = tmp->next;
                }
            }
        }
        tmp2->next = aux;
        l->last = aux;
        l->studentNumber++;
    }
    return 0;
}

//shows the entire list
void showList(typeList *l){
    typeNode *aux = l->first;
    printf("Students in Database... %u\n", l->studentNumber);
    if(!aux){
        printf("Empty list...\n");
    }
    while(aux){
        printf("######### Student's Information ##################\n");
        printf("Name: %s\n", aux->info.studentName);
        printf("Age: %u years\n", aux->info.age);
        printf("Course: %s\n", aux->info.course);
        printf("##################################################\n");
        aux = aux->next;
    }
}

//shows first element of list
void showFirst(typeList *l){
    typeNode *aux = l->first;
    if(aux){
        printf("Showing first student in database...\n");
        printf("######### Student's Information ##################\n");
        printf("Name: %s\n", aux->info.studentName);
        printf("Age: %u years\n", aux->info.age);
        printf("Course: %s\n", aux->info.course);
        printf("##################################################\n");
    }else{
        printf("No element to show data...\n");
    } 
}

//shows last element of list
void showLast(typeList *l){
    typeNode *aux = l->last;
    if(aux){
        printf("Showing last student in database...\n");
        printf("######### Student's Information ##################\n");
        printf("Name: %s\n", aux->info.studentName);
        printf("Age: %u years\n", aux->info.age);
        printf("Course: %s\n", aux->info.course);
        printf("##################################################\n");
    }else{
        printf("No element to show data...\n");
    } 
}

//main function
int main(){
    typeList list;
    createList(&list);
    typeStudent student;

    /*
    strcpy(student.studentName,"Lysandra Formes");
    student.age = 23;
    strcpy(student.course, "Spanish");
    insertLast(&list, student);

    strcpy(student.studentName,"Maikon Brujmant");
    student.age = 27;
    strcpy(student.course, "Industrial Chemistry");
    insertBeginning(&list, student);

    strcpy(student.studentName,"Donald Oathkeeper");
    student.age = 24;
    strcpy(student.course, "Industrial Automation");
    insertBeginning(&list, student);

    strcpy(student.studentName,"Gabriel Takeuchi");
    student.age = 29;
    strcpy(student.course, "Computation Engineering");
    insertLast(&list, student);

    strcpy(student.studentName,"Leonard Polmun");
    student.age = 21;
    strcpy(student.course, "Eletrical Engineering");
    insertBeginning(&list, student);

    strcpy(student.studentName,"Eaulmin Lionheart");
    student.age = 28;
    strcpy(student.course, "Journalism");
    insertLast(&list, student);
    */

    strcpy(student.studentName,"Karol Lyann");
    student.age = 21;
    strcpy(student.course, "Medicine");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Paul James");
    student.age = 24;
    strcpy(student.course, "Architecture");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Anna Fenrold");
    student.age = 26;
    strcpy(student.course, "Design");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Paul Lehroy");
    student.age = 28;
    strcpy(student.course, "Quantum Physics");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Brian Lennard");
    student.age = 22;
    strcpy(student.course, "Engineering");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Dorothea Johnston");
    student.age = 25;
    strcpy(student.course, "Computer Science");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Ying Sun Xen");
    student.age = 31;
    strcpy(student.course, "Economy and Statics");
    orderedInsertionByName(&list, student);

    strcpy(student.studentName,"Ryan Eagle");
    student.age = 25;
    strcpy(student.course, "Music");
    orderedInsertionByName(&list, student);

    showList(&list);
    showFirst(&list);
    showLast(&list);

    searchByName(&list, "Paul Lehroy");
    searchByName(&list, "Thomas Goldfinger");

    modifyName(&list, "Anna Fenrold", "Anna Gomez");
    modifyName(&list, "Paul Lehroy", "Paul Lee Zu");
    modifyName(&list, "Antony Geomano", "Antony Leomano");

    modifyAge(&list,"Paul Lee Zu", 29);
    modifyAge(&list, "Brian Lennard", 27);
    modifyAge(&list, "Hector Zuman", 31);

    modifyCourse(&list, "Paul Lee Zu", "Music");
    modifyCourse(&list, "Brian Lennard", "Mathematics");

    removeByName(&list, "Karol Lyann");
    removeByName(&list, "Paul Lee Zu");
    removeByName(&list, "Brian Lennard");
    removeByName(&list, "Anna Gomez");
    removeByName(&list, "Paul James");
    removeByName(&list, "Dorothea Johnston");
    removeByName(&list, "Ying Sun Xen");
    removeByName(&list, "Ryan Eagle");

    showList(&list);
    showFirst(&list);
    showLast(&list);
    
    return 0;
}
