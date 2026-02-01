#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tipoPessoa{
    char nome[30];
    unsigned idade;
    float salario;
}tipoPessoa;

typedef struct tipoNo{
    struct tipoNo *pai;
    struct tipoNo *esq;
    struct tipoNo *dir;
    tipoPessoa pessoa;
}tipoNo;

typedef struct tipoArvore{
    struct tipoNo *raiz;
}tipoArvore;

void iniciarArvore(tipoArvore *arvore){
    arvore->raiz = NULL;
}

tipoNo *criarNo(tipoPessoa pessoa){
    tipoNo *novoNo = malloc(sizeof(tipoNo));
    if(!novoNo){
        printf("ERRO AO ALOCAR MEMORIA PARA NOVO NO\n");
        exit(-1);
    }
    novoNo->pessoa = pessoa;
    novoNo->pai = NULL;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

void inserirPessoa(tipoPessoa pessoa, tipoArvore *arvore){
    tipoNo *novoNo = criarNo(pessoa);
    tipoNo *aux = arvore->raiz;
    tipoNo *tmp = NULL;
    char inserido = 0;
    if(!aux){
        arvore->raiz = novoNo;
        printf("inserido\n");
    }else{
        while(!inserido){
            if(strcmp(pessoa.nome, aux->pessoa.nome) <= 0){
                if(!aux->esq){
                    aux->esq = novoNo;
                    novoNo->pai = aux;
                    inserido = 1;
                    printf("inserido\n");
                }else{
                    tmp = aux;
                    aux = aux->esq;
                }
            }else{
                if(!aux->dir){
                    aux->dir = novoNo;
                    novoNo->pai = aux;
                    inserido = 1;
                    printf("inserido\n");
                }else{
                    tmp = aux;
                    aux = aux->dir;
                }
            }
        }
    }
}

void mostrarDadosNo(tipoNo *no){
    if(no){
        printf("%s | %u anos | R$ %.2f\n", no->pessoa.nome, no->pessoa.idade, no->pessoa.salario);
        if(no->pai){
            printf("\tpai: %s\n", no->pai->pessoa.nome);
        }else{
            printf("\tno raiz!\n");
        }
        if(no->esq){
            printf("\tfilho esq: %s\n", no->esq->pessoa.nome);
        }else{
            printf("\tsem filho esq...\n");
        }
        if(no->dir){
            printf("\tfilho dir: %s\n", no->dir->pessoa.nome);
        }else{
            printf("\tsem filho dir...\n");
        }
    }
}

void mostrarArvoreAux(tipoNo *no){
    mostrarDadosNo(no);
    if(no->esq){
        mostrarArvoreAux(no->esq);
    }
    if(no->dir){
        mostrarArvoreAux(no->dir);
    }
}

void mostrarArvore(tipoArvore *arvore){
    printf("mostrando dados da arvore\n");
    if(arvore->raiz){
        mostrarArvoreAux(arvore->raiz);
    }
}

void deletarArvoreAux(tipoNo *no){
    if(no){
        deletarArvoreAux(no->esq);
        deletarArvoreAux(no->dir);
        free(no);
        printf("no deletado\n");
    }
}

void deletarArvore(tipoArvore *arvore){
    deletarArvoreAux(arvore->raiz);
    arvore->raiz = NULL;
    printf("arvore deletada\n");
}

char ehFolha(tipoNo *no){
    if(!no->esq && !no->dir){
        return 1;
    }else{
        return 0;
    }
}

char umFilho(tipoNo *no){
    if(no->esq && !no->dir || !no->esq && no->dir){
        return 1;
    }else{
        return 0;
    }
}

tipoNo *procurarNo(char *nome, tipoNo *raizBusca){
    tipoNo *aux = raizBusca;
    while(aux){
        int res = strcmp(nome, aux->pessoa.nome);
        if(!res){
            return aux;
        }else if (res < 0){
            aux = aux->esq;
        }else{
            aux = aux->dir;
        }
    }
    return NULL;
}

tipoNo *sucessorNo(tipoNo *no){
    if(!no->esq){
        return no;
    }else{
        return sucessorNo(no->esq);
    }
}

void deletarNoAux(char *nome, tipoArvore *arvore, tipoNo *raizBusca){
    tipoNo *aux = procurarNo(nome, raizBusca);
    if(aux){
        if(aux == arvore->raiz){ //o no para deletar eh o raiz
            if(ehFolha(aux)){
                arvore->raiz = NULL;
                free(aux);
                printf("no deletado\n");
            }else{
                if(umFilho(aux)){ //no raiz tem um filho?
                    if(aux->esq){
                        aux->pessoa = aux->esq->pessoa;
                        deletarNoAux(aux->esq->pessoa.nome, arvore, aux->dir);
                    }else{
                        aux->pessoa = aux->dir->pessoa;
                        deletarNoAux(aux->dir->pessoa.nome, arvore, aux->dir);
                    }
                }else{ //no raiz tem dois filhos
                    tipoNo *sucessor = sucessorNo(aux->dir);
                    printf("encontrei o sucessor %s\n", sucessor->pessoa.nome);
                    aux->pessoa = sucessor->pessoa;
                    deletarNoAux(sucessor->pessoa.nome, arvore, aux->dir);
                }
            }
        }else{ //nao eh o no raiz
            if(ehFolha(aux)){ //eh um no folha
                if(aux->pai->esq == aux){
                    aux->pai->esq = NULL;
                }else{
                    aux->pai->dir = NULL;
                }
                free(aux);
                printf("no deletado\n");
            }else{
                if(umFilho(aux)){ //no tem um filho?
                    if(aux->esq){
                        aux->pessoa = aux->esq->pessoa;
                        deletarNoAux(aux->esq->pessoa.nome, arvore, aux->dir);
                    }else{
                        aux->pessoa = aux->dir->pessoa;
                        deletarNoAux(aux->dir->pessoa.nome, arvore, aux->dir);
                    }
                }else{ //no tem dois filhos?
                    tipoNo *sucessor = sucessorNo(aux->dir);
                    printf("encontrei o sucessor %s\n", sucessor->pessoa.nome);
                    aux->pessoa = sucessor->pessoa;
                    deletarNoAux(sucessor->pessoa.nome, arvore, aux->dir);
                }
            }
        }
    }else{
        printf("nenhum nome encontrado para ser deletado\n");
    }
}

void deletarNo(char *nome, tipoArvore *arvore){
    deletarNoAux(nome, arvore, arvore->raiz);
}

void main(){
    tipoArvore arvore;
    iniciarArvore(&arvore);
    tipoPessoa pessoa;

    strcpy(pessoa.nome, "Genivaldo");
    pessoa.idade = 55;
    pessoa.salario = 4456.79;
    inserirPessoa(pessoa, &arvore);

    strcpy(pessoa.nome, "Roberto");
    pessoa.idade = 38;
    pessoa.salario = 2116.79;
    inserirPessoa(pessoa, &arvore);

    strcpy(pessoa.nome, "Daniela");
    pessoa.idade = 24;
    pessoa.salario = 9841.43;
    inserirPessoa(pessoa, &arvore);

    strcpy(pessoa.nome, "Fernanda");
    pessoa.idade = 41;
    pessoa.salario = 59325.95;
    inserirPessoa(pessoa, &arvore);
    
    strcpy(pessoa.nome, "Tereza");
    pessoa.idade = 73;
    pessoa.salario = 23112.79;
    inserirPessoa(pessoa, &arvore);

    strcpy(pessoa.nome, "Otovaldo");
    pessoa.idade = 41;
    pessoa.salario = 89505.79;
    inserirPessoa(pessoa, &arvore);

    mostrarArvore(&arvore);

    deletarNo("Roberto", &arvore);
    mostrarArvore(&arvore);

    deletarArvore(&arvore);
    mostrarArvore(&arvore);
}