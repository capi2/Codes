#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tipoAluno{
    char nome[20];
    float coeficiente;
    unsigned int idade;
}tipoAluno;

void mostrarAlunos(tipoAluno *vetorAlunos, int tam){
    for(int i = 0; i < tam; i++){
        printf("Nome: %20s | Coeficiente: %.2f | Idade: %u\n", vetorAlunos[i].nome, vetorAlunos[i].coeficiente, vetorAlunos[i].idade);
    }
}

void insertion_sort_nome(tipoAluno *vetorAlunos, int tam){
    tipoAluno aluno;
    for(int j = 1; j < tam; j++){
        aluno = vetorAlunos[j];
        int i = j - 1;
        while(j >= 0 && strcmp(vetorAlunos[i].nome,aluno.nome) > 0){
            vetorAlunos[i+1] = vetorAlunos[i];
            i -= 1;
        }
        vetorAlunos[i+1] = aluno;
    }
}

void insertion_sort_idade(tipoAluno *vetorAlunos, int tam){
    tipoAluno aluno;
    for(int j = 1; j < tam; j++){
        aluno = vetorAlunos[j];
        int i = j - 1;
        while(j >= 0 && vetorAlunos[i].idade > aluno.idade){
            vetorAlunos[i+1] = vetorAlunos[i];
            i -= 1;
        }
        vetorAlunos[i+1] = aluno;
    }
}

void insertion_sort_coeficiente(tipoAluno *vetorAlunos, int tam){
    tipoAluno aluno;
    for(int j = 1; j < tam; j++){
        aluno = vetorAlunos[j];
        int i = j - 1;
        while(j >= 0 && vetorAlunos[i].coeficiente > aluno.coeficiente){
            vetorAlunos[i+1] = vetorAlunos[i];
            i -= 1;
        }
        vetorAlunos[i+1] = aluno;
    }
}

void bubble_sort_nome(tipoAluno *vetorAlunos, int tam){
    for(int i = 0; i < tam; i++){
        for(int j = tam-1; j > i; j -= 1){
            if(strcmp(vetorAlunos[j].nome, vetorAlunos[j-1].nome) < 0){
                tipoAluno aux = vetorAlunos[j];
                vetorAlunos[j] = vetorAlunos[j-1];
                vetorAlunos[j-1] = aux;
            }
        }
    }
}

void bubble_sort_idade(tipoAluno *vetorAlunos, int tam){
    for(int i = 0; i < tam; i++){
        for(int j = tam-1; j > i; j -= 1){
            if(vetorAlunos[j].idade < vetorAlunos[j-1].idade){
                tipoAluno aux = vetorAlunos[j];
                vetorAlunos[j] = vetorAlunos[j-1];
                vetorAlunos[j-1] = aux;
            }
        }
    }
}

void bubble_sort_coeficiente(tipoAluno *vetorAlunos, int tam){
    for(int i = 0; i < tam; i++){
        for(int j = tam-1; j > i; j -= 1){
            if(vetorAlunos[j].coeficiente < vetorAlunos[j-1].coeficiente){
                tipoAluno aux = vetorAlunos[j];
                vetorAlunos[j] = vetorAlunos[j-1];
                vetorAlunos[j-1] = aux;
            }
        }
    }
}

void merge_nome(tipoAluno *vetorAlunos, int inicio, int meio, int fim){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    tipoAluno *aux1 = calloc(n1, sizeof(tipoAluno));
    tipoAluno *aux2 = calloc(n2, sizeof(tipoAluno));
    for(int i = 0; i < n1; i++){
        aux1[i] = vetorAlunos[inicio + i];
    }
    for(int j = 0; j < n2; j++){
        aux2[j] = vetorAlunos[meio + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = inicio;
    while(i < n1 && j < n2){
        if(strcmp(aux1[i].nome, aux2[j].nome) <= 0){
            vetorAlunos[k] = aux1[i];
            i++;
        }else{
            vetorAlunos[k] = aux2[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        vetorAlunos[k] = aux1[i];
        i++; k++;
    }
    while(j < n2){
        vetorAlunos[k] = aux2[j];
        j++, k++;
    }
    free(aux1);
    free(aux2);
}

void merge_sort_nm(tipoAluno *vetorAlunos, int inicio, int fim){
    if(inicio >= fim){
        return;
    }
    int meio = (inicio + fim)/2;
    merge_sort_nm(vetorAlunos, inicio, meio);
    merge_sort_nm(vetorAlunos, meio + 1, fim);
    merge_nome(vetorAlunos, inicio, meio, fim);
}

void merge_sort_nome(tipoAluno *vetorAlunos, int tam){
    merge_sort_nm(vetorAlunos, 0, tam-1);
}

void merge_idade(tipoAluno *vetorAlunos, int inicio, int meio, int fim){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    tipoAluno *aux1 = calloc(n1, sizeof(tipoAluno));
    tipoAluno *aux2 = calloc(n2, sizeof(tipoAluno));
    for(int i = 0; i < n1; i++){
        aux1[i] = vetorAlunos[inicio + i];
    }
    for(int j = 0; j < n2; j++){
        aux2[j] = vetorAlunos[meio + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = inicio;
    while(i < n1 && j < n2){
        if(aux1[i].idade <= aux2[j].idade){
            vetorAlunos[k] = aux1[i];
            i++;
        }else{
            vetorAlunos[k] = aux2[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        vetorAlunos[k] = aux1[i];
        i++; k++;
    }
    while(j < n2){
        vetorAlunos[k] = aux2[j];
        j++, k++;
    }
    free(aux1);
    free(aux2);
}

void merge_sort_id(tipoAluno *vetorAlunos, int inicio, int fim){
    if(inicio >= fim){
        return;
    }
    int meio = (inicio + fim)/2;
    merge_sort_id(vetorAlunos, inicio, meio);
    merge_sort_id(vetorAlunos, meio + 1, fim);
    merge_idade(vetorAlunos, inicio, meio, fim);
}

void merge_sort_idade(tipoAluno *vetorAlunos, int tam){
    merge_sort_id(vetorAlunos, 0, tam-1);
}

void merge_coeficiente(tipoAluno *vetorAlunos, int inicio, int meio, int fim){
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    tipoAluno *aux1 = calloc(n1, sizeof(tipoAluno));
    tipoAluno *aux2 = calloc(n2, sizeof(tipoAluno));
    for(int i = 0; i < n1; i++){
        aux1[i] = vetorAlunos[inicio + i];
    }
    for(int j = 0; j < n2; j++){
        aux2[j] = vetorAlunos[meio + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = inicio;
    while(i < n1 && j < n2){
        if(aux1[i].coeficiente <= aux2[j].coeficiente){
            vetorAlunos[k] = aux1[i];
            i++;
        }else{
            vetorAlunos[k] = aux2[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        vetorAlunos[k] = aux1[i];
        i++; k++;
    }
    while(j < n2){
        vetorAlunos[k] = aux2[j];
        j++, k++;
    }
    free(aux1);
    free(aux2);
}

void merge_sort_coef(tipoAluno *vetorAlunos, int inicio, int fim){
    if(inicio >= fim){
        return;
    }
    int meio = (inicio + fim)/2;
    merge_sort_coef(vetorAlunos, inicio, meio);
    merge_sort_coef(vetorAlunos, meio + 1, fim);
    merge_coeficiente(vetorAlunos, inicio, meio, fim);
}

void merge_sort_coeficiente(tipoAluno *vetorAlunos, int tam){
    merge_sort_coef(vetorAlunos, 0, tam-1);
}

int particao_nome(tipoAluno *vetorAlunos, int inicio, int fim){
    tipoAluno x = vetorAlunos[fim];
    int i = inicio - 1;
    for(int j = inicio; j < fim; j++){
        if(strcmp(vetorAlunos[j].nome, x.nome) <= 0){
            i++;
            tipoAluno aux1 = vetorAlunos[i];
            vetorAlunos[i] = vetorAlunos[j];
            vetorAlunos[j] = aux1;
        }
    }
    tipoAluno aux2 = vetorAlunos[i+1];
    vetorAlunos[i+1] = vetorAlunos[fim];
    vetorAlunos[fim] = aux2;
    return i + 1;
}

void quick_sort_nm(tipoAluno *vetorAlunos, int inicio, int fim){
    if(inicio < fim){
        int meio = particao_nome(vetorAlunos, inicio, fim);
        quick_sort_nm(vetorAlunos, inicio, meio - 1);
        quick_sort_nm(vetorAlunos, meio + 1, fim);
    }
}

void quick_sort_nome(tipoAluno *vetorAlunos, int tam){
    quick_sort_nm(vetorAlunos, 0, tam-1);
}

int particao_idade(tipoAluno *vetorAlunos, int inicio, int fim){
    tipoAluno x = vetorAlunos[fim];
    int i = inicio - 1;
    for(int j = inicio; j < fim; j++){
        if(vetorAlunos[j].idade <= x.idade){
            i++;
            tipoAluno aux1 = vetorAlunos[i];
            vetorAlunos[i] = vetorAlunos[j];
            vetorAlunos[j] = aux1;
        }
    }
    tipoAluno aux2 = vetorAlunos[i+1];
    vetorAlunos[i+1] = vetorAlunos[fim];
    vetorAlunos[fim] = aux2;
    return i + 1;
}

void quick_sort_id(tipoAluno *vetorAlunos, int inicio, int fim){
    if(inicio < fim){
        int meio = particao_idade(vetorAlunos, inicio, fim);
        quick_sort_id(vetorAlunos, inicio, meio - 1);
        quick_sort_id(vetorAlunos, meio + 1, fim);
    }
}

void quick_sort_idade(tipoAluno *vetorAlunos, int tam){
    quick_sort_id(vetorAlunos, 0, tam-1);
}

int particao_coeficiente(tipoAluno *vetorAlunos, int inicio, int fim){
    tipoAluno x = vetorAlunos[fim];
    int i = inicio - 1;
    for(int j = inicio; j < fim; j++){
        if(vetorAlunos[j].coeficiente <= x.coeficiente){
            i++;
            tipoAluno aux1 = vetorAlunos[i];
            vetorAlunos[i] = vetorAlunos[j];
            vetorAlunos[j] = aux1;
        }
    }
    tipoAluno aux2 = vetorAlunos[i+1];
    vetorAlunos[i+1] = vetorAlunos[fim];
    vetorAlunos[fim] = aux2;
    return i + 1;
}

void quick_sort_coef(tipoAluno *vetorAlunos, int inicio, int fim){
    if(inicio < fim){
        int meio = particao_coeficiente(vetorAlunos, inicio, fim);
        quick_sort_coef(vetorAlunos, inicio, meio - 1);
        quick_sort_coef(vetorAlunos, meio + 1, fim);
    }
}

void quick_sort_coeficiente(tipoAluno *vetorAlunos, int tam){
    quick_sort_coef(vetorAlunos, 0, tam-1);
}

int main(){
    tipoAluno vetorAlunos[10];
    tipoAluno aluno;
    
    strcpy(aluno.nome, "Patrick Monteiro");
    aluno.coeficiente = 6.75;
    aluno.idade = 20;
    vetorAlunos[0] = aluno;

    strcpy(aluno.nome, "Gizelle Cardoso");
    aluno.coeficiente = 8.44;
    aluno.idade = 19;
    vetorAlunos[1] = aluno;

    strcpy(aluno.nome, "Heitor Silva");
    aluno.coeficiente = 9.01;
    aluno.idade = 22;
    vetorAlunos[2] = aluno;

    strcpy(aluno.nome, "Ricardo Menezes");
    aluno.coeficiente = 7.78;
    aluno.idade = 21;
    vetorAlunos[3] = aluno;

    strcpy(aluno.nome, "Olga Kohm");
    aluno.coeficiente = 8.92;
    aluno.idade = 24;
    vetorAlunos[4] = aluno;

    strcpy(aluno.nome, "Alberto Figueiredo");
    aluno.coeficiente = 5.62;
    aluno.idade = 17;
    vetorAlunos[5] = aluno;

    strcpy(aluno.nome, "William Pinto");
    aluno.coeficiente = 6.23;
    aluno.idade = 18;
    vetorAlunos[6] = aluno;

    strcpy(aluno.nome, "Marina Verde");
    aluno.coeficiente = 9.51;
    aluno.idade = 25;
    vetorAlunos[7] = aluno;

    strcpy(aluno.nome, "Yamada Clementino");
    aluno.coeficiente = 8.82;
    aluno.idade = 24;
    vetorAlunos[8] = aluno;

    strcpy(aluno.nome, "Jose dos Santos");
    aluno.coeficiente = 7.99;
    aluno.idade = 22;
    vetorAlunos[9] = aluno;

    //insertion_sort_coeficiente(vetorAlunos, 10);
    //bubble_sort_coeficiente(vetorAlunos, 10);
    //bubble_sort_idade(vetorAlunos, 10);
    //bubble_sort_nome(vetorAlunos, 10);
    //merge_sort_idade(vetorAlunos, 10);
    //merge_sort_coeficiente(vetorAlunos, 10);
    //merge_sort_nome(vetorAlunos, 10);
    //quick_sort_nome(vetorAlunos, 10);
    //quick_sort_idade(vetorAlunos, 10);
    //quick_sort_coeficiente(vetorAlunos, 10);

    mostrarAlunos(vetorAlunos, 10);

}