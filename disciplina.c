#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct disciplina_t{
    char nome[40];
    char codigo[10];
    char professor[30];
    unsigned periodo;
    unsigned horas;
    unsigned creditos;
}disciplina_t;

typedef struct no_t{
    disciplina_t disciplina;
    struct no_t *antes;
    struct no_t *depois;
}no_t;

typedef struct lista_t{
    no_t *inicio;
    unsigned quantidade;
}lista_t;

void iniciarLista(lista_t *lista){
    lista->inicio = NULL;
    lista->quantidade = 0;
}

no_t *criarNo(disciplina_t info_disc){
    no_t *aux = malloc(sizeof(no_t));
    if(!aux){
        printf("[ERRO] Memoria insuficiente para alocar ponteiro do no!\n");
        exit(EXIT_FAILURE); 
    }
    aux->disciplina = info_disc;
    aux->antes = NULL;
    aux->depois = NULL;
    return aux;
}

void inserirNoInicio(lista_t *lista, disciplina_t info_disc){
    no_t *aux = criarNo(info_disc);
    if(!lista->inicio){
        lista->inicio = aux;
    }else{
        lista->inicio->antes = aux;
        aux->depois = lista->inicio;
        lista->inicio = aux;
    }
    lista->quantidade++;
}

void inserirNoOrdenado(lista_t *lista, disciplina_t info_disc){
    no_t *aux = criarNo(info_disc);
    no_t *tmp1 = NULL;
    no_t *tmp2 = lista->inicio;
    if(!lista->inicio){
        lista->inicio = aux;
        lista->quantidade++;
    }else if(strcmp(aux->disciplina.nome, tmp2->disciplina.nome) < 0){
            aux->depois = tmp2;
            lista->inicio = aux;
            tmp2->antes = aux;
            lista->quantidade++;
    }else{
        tmp1 = tmp2;
        tmp2 = tmp2->depois;
        while(tmp2 && strcmp(aux->disciplina.nome, tmp2->disciplina.nome) > 0){
            tmp1 = tmp2;
            tmp2 = tmp2->depois;
        }
        tmp1->depois = aux;
        aux->antes = tmp1;
        aux->depois = tmp2;
        if(tmp2){
            tmp2->antes = aux;  
        }
        lista->quantidade++;   
    }   
}

void deletarDisciplina(lista_t *lista, char *disciplina_nome){
    no_t *aux = lista->inicio;
    no_t *tmp = NULL;
    if(aux){
        if(!strcmp(disciplina_nome, aux->disciplina.nome)){
            lista->inicio = aux->depois;
            if(aux->depois){
                aux->depois->antes = NULL;
            }
            lista->quantidade--;
            free(aux);
            printf("Disciplina %s foi removida!\n", disciplina_nome);
            return;
        }else{
            tmp = aux;
            aux = aux->depois;
            while(aux){
                if(!strcmp(disciplina_nome, aux->disciplina.nome)){
                    aux->antes->depois = aux->depois;
                    if(aux->depois){
                        aux->depois->antes = aux->antes;
                    }
                    lista->quantidade--;
                    free(aux);
                    printf("Disciplina %s foi removida!\n", disciplina_nome);
                    return;
                }else{
                    tmp = aux;
                    aux = aux->depois;
                }
            }
        }
        printf("Nenhuma disciplina com o nome '%s' foi encontrada para ser removida...\n", disciplina_nome);
    }else{
        printf("Nada para deletar, a lista esta vazia!\n");
    }
}

void buscarDisciplina(lista_t *lista, char *disciplina_nome){
    no_t *aux = lista->inicio;
    while(aux){
        if(!strcmp(aux->disciplina.nome, disciplina_nome)){
            printf("[SUCESSO] Disciplina encontrada! Mostrando informacoes...\n");
            printf("-----------------------------------------------------\n");
            printf("Nome: %s | Codigo: %s\n", aux->disciplina.nome, aux->disciplina.codigo);
            printf("Professor: %s\n", aux->disciplina.professor);
            printf("Periodo: %u | Carga Horaria: %u | Creditos: %u\n", aux->disciplina.periodo, aux->disciplina.horas, aux->disciplina.creditos);
            printf("Antes: %s\n", aux->antes ? aux->antes->disciplina.nome : "nada");
            printf("Proximo: %s\n", aux->depois ? aux->depois->disciplina.nome: "nada");
            printf("-----------------------------------------------------\n");
            return;
        }else{
            aux = aux->depois;
        }
    }
    printf("[ERRO] Nenhuma disciplina chamada '%s' foi encontrada na lista...\n", disciplina_nome);
}

void mostrarLista(lista_t *lista){
    no_t *aux = lista->inicio;
    printf("Disciplinas na lista: %u\n", lista->quantidade);
    while(aux){
        printf("-----------------------------------------------------\n");
        printf("Nome: %s | Codigo: %s\n", aux->disciplina.nome, aux->disciplina.codigo);
        printf("Professor: %s\n", aux->disciplina.professor);
        printf("Periodo: %u | Carga Horaria: %u | Creditos: %u\n", aux->disciplina.periodo, aux->disciplina.horas, aux->disciplina.creditos);
        printf("Antes: %s\n", aux->antes ? aux->antes->disciplina.nome: "nada");
        printf("Proximo: %s\n", aux->depois ? aux->depois->disciplina.nome: "nada");
        printf("-----------------------------------------------------\n");
        aux = aux->depois;
    }
}

int main(){
    lista_t lista;
    iniciarLista(&lista);
    disciplina_t disciplina;

    strcpy(disciplina.nome, "Introducao a Computacao");
    strcpy(disciplina.codigo, "ICC001");
    strcpy(disciplina.professor, "Bruno Lopes");
    disciplina.periodo = 1;
    disciplina.horas = 90;
    disciplina.creditos = 5;
    inserirNoOrdenado(&lista, disciplina);

    strcpy(disciplina.nome, "Paradigmas de Linguagem de Programacao");
    strcpy(disciplina.codigo, "ICC029");
    strcpy(disciplina.professor, "Clodoaldo dos Santos");
    disciplina.periodo = 4;
    disciplina.horas = 60;
    disciplina.creditos = 5;
    inserirNoOrdenado(&lista, disciplina);

    strcpy(disciplina.nome, "Organizacao dos Computadores");
    strcpy(disciplina.codigo, "ICC015");
    strcpy(disciplina.professor, "Juarez de Sciuva");
    disciplina.periodo = 3;
    disciplina.horas = 60;
    disciplina.creditos = 4;
    inserirNoOrdenado(&lista, disciplina);

    strcpy(disciplina.nome, "Introducao a Engenharia de Software");
    strcpy(disciplina.codigo, "ICC014");
    strcpy(disciplina.professor, "Tereza Silva");
    disciplina.periodo = 5;
    disciplina.horas = 90;
    disciplina.creditos = 5;
    inserirNoOrdenado(&lista, disciplina);

    strcpy(disciplina.nome, "Algoritmos e Estruturas de Dados II");
    strcpy(disciplina.codigo, "ICC003");
    strcpy(disciplina.professor, "Catarina Silveira");
    disciplina.periodo = 3;
    disciplina.horas = 90;
    disciplina.creditos = 5;
    inserirNoOrdenado(&lista, disciplina);

    strcpy(disciplina.nome, "Linguagens Formais e Automatos");
    strcpy(disciplina.codigo, "ICC010");
    strcpy(disciplina.professor, "Adamir Santiago");
    disciplina.periodo = 2;
    disciplina.horas = 60;
    disciplina.creditos = 4;
    inserirNoOrdenado(&lista, disciplina);

    strcpy(disciplina.nome, "Projeto e Analise de Algoritmos");
    strcpy(disciplina.codigo, "ICC025");
    strcpy(disciplina.professor, "Robson Pedro");
    disciplina.periodo = 5;
    disciplina.horas = 60;
    disciplina.creditos = 4;
    inserirNoOrdenado(&lista, disciplina);

    mostrarLista(&lista);

    buscarDisciplina(&lista, "Introducao a Computacao");
    deletarDisciplina(&lista, "Introducao a Computacao");
    buscarDisciplina(&lista, "Introducao a Computacao");
    
    mostrarLista(&lista);
}