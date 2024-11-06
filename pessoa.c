#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct pessoa_t{
    char nome[30];
    unsigned idade;
    char genero;
}pessoa_t;

typedef struct no_t{
    pessoa_t pessoa;
    struct no_t *depois;
}no_t;

typedef struct lista_t{
    struct no_t *inicio;
    unsigned num_pessoas;
}lista_t;

void iniciarLista(lista_t *lista){
    lista->inicio = NULL;
    lista->num_pessoas = 0;
}

no_t *criarNoPessoa(pessoa_t info){
    no_t *aux = malloc(sizeof(no_t));
    if(!aux){
        printf("Problema ao alocar memoria para no da pessoa!\n");
        exit(-1);
    }
    aux->pessoa = info;
    aux->depois = NULL;
    return aux;
}

void inserirNaLista(pessoa_t info, lista_t *lista){
    no_t *aux = criarNoPessoa(info);
    if(!lista->inicio){
        lista->inicio = aux;
        lista->num_pessoas++;
    }else{
        aux->depois = lista->inicio;
        lista->inicio = aux;
        lista->num_pessoas++;
    }
}

void inserirOrdenado(pessoa_t info, lista_t *lista){
    no_t *aux = criarNoPessoa(info);
    no_t *tmp = lista->inicio;
    no_t *tmp2 = NULL;
    if(!lista->inicio){
        lista->inicio = aux;
        lista->num_pessoas++;
    }else{
        if(strcmp(aux->pessoa.nome, tmp->pessoa.nome) < 0){
            aux->depois = tmp;
            lista->inicio = aux;
            lista->num_pessoas++;
        }else{
            while(tmp && strcmp(aux->pessoa.nome, tmp->pessoa.nome) > 0){
                tmp2 = tmp;
                tmp = tmp->depois;
            }
            if(tmp){
                tmp2->depois = aux;
                aux->depois = tmp;

                lista->num_pessoas++;
            }else{
                tmp2->depois = aux;
                lista->num_pessoas++;
            }
        }
    }
}

void deletarPessoa(lista_t *lista, char *nome){
    no_t *aux = lista->inicio;
    no_t *tmp = NULL;
    if(!strcmp(nome, aux->pessoa.nome)){
        lista->inicio = aux->depois;
        free(aux);
        lista->num_pessoas--;
        printf("%s foi deletado com sucesso!\n", nome);
    }else{
        tmp = aux;
        aux = aux->depois;
        while(aux){
            if(!strcmp(nome, aux->pessoa.nome)){
                tmp->depois = aux->depois;
                free(aux);
                lista->num_pessoas--;
                printf("%s foi deletado com sucesso!\n", nome);
                return;
            }else{
                tmp = aux;
                aux = aux->depois;
            }
        }
        printf("[ERRO] %s nao foi encontrado na lista para ser deletado...\n", nome);
    }
}

void buscarPessoa(lista_t *lista, char *nome){
    no_t *aux = lista->inicio;
    while(aux){
        if(!strcmp(nome, aux->pessoa.nome)){
            printf("Pessoa encontrada!\n");
            printf("---------------------------------------------------\n");
            printf("Nome: %s\n", aux->pessoa.nome);
            printf("Idade: %u\n", aux->pessoa.idade);
            printf("Genero: %c\n", aux->pessoa.genero);
            printf("Pessoa depois: %s\n", aux->depois->pessoa.nome);
            printf("---------------------------------------------------\n");
            return;
        }else{
            aux = aux->depois;
        }
    }
    printf("[ERRO] %s nao foi encontrado na lista...\n", nome);  
}

void mostrarLista(lista_t *lista){
    no_t *aux = lista->inicio;
    printf("Numero de pessoas na lista: %u\n", lista->num_pessoas);
    while(aux){
        printf("---------------------------------------------------\n");
        printf("Nome: %s\n", aux->pessoa.nome);
        printf("Idade: %u\n", aux->pessoa.idade);
        printf("Genero: %c\n", aux->pessoa.genero);
        printf("Pessoa depois: %s\n", aux->depois->pessoa.nome);
        printf("---------------------------------------------------\n");
        aux = aux->depois;
    }
}

int main(){
    lista_t lista;
    iniciarLista(&lista);

    pessoa_t pessoa;

    strcpy(pessoa.nome, "Kaio Silva");
    pessoa.idade = 23;
    pessoa.genero = 'm';
    inserirOrdenado(pessoa, &lista);

    strcpy(pessoa.nome, "Nolan Bitterncourt");
    pessoa.idade = 24;
    pessoa.genero = 'm';
    inserirOrdenado(pessoa, &lista);

    strcpy(pessoa.nome, "Leonardo Barreto");
    pessoa.idade = 21;
    pessoa.genero = 'm';
    inserirOrdenado(pessoa, &lista);

    strcpy(pessoa.nome, "Euler dos Santos");
    pessoa.idade = 27;
    pessoa.genero = 'm';
    inserirOrdenado(pessoa, &lista);

    strcpy(pessoa.nome, "Pamela Brandao");
    pessoa.idade = 19;
    pessoa.genero = 'f';
    inserirOrdenado(pessoa, &lista);

    strcpy(pessoa.nome, "Bruna Dantas");
    pessoa.idade = 25;
    pessoa.genero = 'f';
    inserirOrdenado(pessoa, &lista);

    mostrarLista(&lista);

    deletarPessoa(&lista, "Euler dos Santos");
    deletarPessoa(&lista, "Lorena Cavalcanti");

    mostrarLista(&lista);

    buscarPessoa(&lista, "Pamela Brandao");
    buscarPessoa(&lista, "Teodorio Bastos");

}