#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tipoCidade{
    char nome[30];
    float distancia;
}tipoCidade;

typedef struct tipoNo{
    tipoCidade cidade;
    struct tipoNo *prox;
}tipoNo;

typedef struct tipoLista{
    char nomeCidade[30];
    struct tipoNo *inicio;
    struct tipoNo *fim;
}tipoLista;

typedef struct tipoGrafo{
    struct tipoLista *vetorCidades;
}tipoGrafo;

void iniciarLista(tipoLista *lista){
    lista->inicio = NULL;
    lista->fim = NULL;
}

tipoNo *criarNo(tipoCidade cidade){
    tipoNo *novoNo = malloc(sizeof(tipoNo));
    if(!novoNo){
        printf("erro ao alocar memoria para novo no!\n");
        exit(-1);
    }
    novoNo->cidade = cidade;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirNo(tipoLista *lista, tipoCidade cidade){
    tipoNo *novoNo = criarNo(cidade);
    if(!lista->inicio){
        lista->inicio = novoNo;
        lista->fim = novoNo;
    }else{
        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
}

void mostrarLista(tipoLista *lista){
    tipoNo *aux = lista->inicio;
    while(aux){
        printf("\tCidade: %s | Distancia: %.2f\n", aux->cidade.nome, aux->cidade.distancia);
        aux = aux->prox;
    }
}

void inserirCidadeNoGrafo(char *cidadePrincipal, tipoCidade vizinho, tipoGrafo grafo, unsigned tamGrafo){
    for(int i = 0; i < tamGrafo; i++){
        if(!strcmp(cidadePrincipal, grafo.vetorCidades[i].nomeCidade)){
            inserirNo(&grafo.vetorCidades[i], vizinho);
        }
        if(!strcmp(grafo.vetorCidades[i].nomeCidade, vizinho.nome)){
            tipoCidade cidade;
            strcpy(cidade.nome, cidadePrincipal);
            cidade.distancia = vizinho.distancia;
            inserirNo(&grafo.vetorCidades[i], cidade);
        }
    }
}

void mostrarGrafo(tipoGrafo grafo, unsigned tamGrafo){
    for(int i = 0; i < tamGrafo; i++){
        printf("Cidade principal: %s\n", grafo.vetorCidades[i].nomeCidade);
        mostrarLista(&grafo.vetorCidades[i]);
    }
}

void iniciarGrafo(tipoGrafo grafo, unsigned tamGrafo){
    for(int i = 0; i < tamGrafo; i++){
        iniciarLista(&grafo.vetorCidades[i]);
    }
}

void apagarLista(tipoLista *lista){
    tipoNo *aux = lista->inicio;
    lista->inicio = NULL;
    while(aux){
        tipoNo *tmp = aux;
        aux = aux->prox;
        free(aux);
    }
}

void apagarGrafo(tipoGrafo grafo, unsigned tamGrafo){
    for(int i = 0; i < tamGrafo; i++){
        apagarLista(&grafo.vetorCidades[i]);
    }
}

int main(){
    tipoGrafo grafo;
    unsigned tamGrafo = 5;
    tipoLista *vetorCidades = malloc(sizeof(tipoLista)*tamGrafo);
    grafo.vetorCidades = vetorCidades;
    iniciarGrafo(grafo, tamGrafo);
    
    char nomeCidades[5][30] = {"Sao Paulo", "Rio de Janeiro", "Manaus", "Santa Catarina", "Recife"};
    for(int i = 0; i < 5; i++){
        strcpy(grafo.vetorCidades[i].nomeCidade, nomeCidades[i]);
    }
    tipoCidade cidade;

    strcpy(cidade.nome, "Rio de Janeiro");
    cidade.distancia = 460;
    inserirCidadeNoGrafo("Sao Paulo", cidade, grafo, tamGrafo);

    strcpy(cidade.nome, "Manaus");
    cidade.distancia = 7700;
    inserirCidadeNoGrafo("Sao Paulo", cidade, grafo, tamGrafo);
    
    strcpy(cidade.nome, "Santa Catarina");
    cidade.distancia = 1500;
    inserirCidadeNoGrafo("Rio de Janeiro", cidade, grafo, tamGrafo);

    strcpy(cidade.nome, "Recife");
    cidade.distancia = 3450;
    inserirCidadeNoGrafo("Manaus", cidade, grafo, tamGrafo);

    mostrarGrafo(grafo, tamGrafo);
    apagarGrafo(grafo, tamGrafo);
    free(vetorCidades);
}