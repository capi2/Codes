#include <stdio.h>
#include <string.h>

struct Pessoa{
    char nome[20];
    unsigned idade;
};

int main(){
    struct Pessoa pessoa;
    strcpy(pessoa.nome, "Thiago Santos");
    pessoa.idade = 24;

    printf("%s\n", pessoa.nome);
    printf("%d\n", pessoa.idade);

    strcpy(pessoa.nome, "Antonio Vieira");
    pessoa.idade = 21;

    printf("%s\n", pessoa.nome);
    printf("%d\n", pessoa.idade);
}