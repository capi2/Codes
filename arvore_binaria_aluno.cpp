#include <iostream>
#include <stdlib.h>

typedef struct tipoAluno{
    std::string nome;
    unsigned int idade;
    std::string matricula;
    float coeficiente;
}tipoAluno;

typedef struct tipoNo{
    tipoAluno aluno_info;
    struct tipoNo *pai;
    struct tipoNo *esquerda;
    struct tipoNo *direita;
}tipoNo;

typedef struct tipoArvore{
    struct tipoNo *raiz;
    unsigned int numNos;
}tipoArvore;

void iniciarArvore(tipoArvore *arvore){
    arvore->raiz = NULL;
    arvore->numNos = 0;
}

tipoNo *criarNoAluno(tipoAluno informacoes_aluno){
    tipoNo *no = new tipoNo();
    no->aluno_info = informacoes_aluno;
    no->pai = NULL;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

void inserirAluno(tipoArvore *arvore, tipoAluno informacoes_aluno){
    tipoNo *z = criarNoAluno(informacoes_aluno);
    tipoNo *x = arvore->raiz;
    tipoNo *y = NULL;
    while(x){
        y = x;
        if(z->aluno_info.nome.compare(x->aluno_info.nome) < 0){
            x = x->esquerda;
        }else{
            x = x->direita;
        }
    }
    z->pai = y;
    if(!y){
        arvore->raiz = z;
    }else if(z->aluno_info.nome.compare(y->aluno_info.nome) < 0){
        y->esquerda = z;
    }else{
        y->direita = z;
    }
    arvore->numNos++;
}

//percorre a arvore e mostra o conteudo dos nos
void mostrarArvore(tipoNo *no){
    if(no){
        mostrarArvore(no->esquerda);
        std::cout << "Nome: " << no->aluno_info.nome << std::endl;
        std::cout << "Idade: " << no->aluno_info.idade << std::endl; 
        std::cout << "Matricula: " << no->aluno_info.matricula << std::endl; 
        std::cout << "Coeficiente: " << no->aluno_info.coeficiente << std::endl;
        std::cout << std::endl;
        mostrarArvore(no->direita);
    }
}

//percorre a arvore e mostra o no, seu ancestral e seus filhos, se houver
void mostrarArvore2(tipoNo *no){
    if(no){
        mostrarArvore2(no->esquerda);
        std::cout << "No: " << no->aluno_info.nome << std::endl;
        if(no->pai){
            std::cout << "\tAncestral: " << no->pai->aluno_info.nome << std::endl;
        }else{
            std::cout << "\tNo raiz da arvore!" << std::endl;
        }
        if(no->esquerda){
            std::cout << "\tFilho esquerda: " << no->esquerda->aluno_info.nome << std::endl;
        }else{
            std::cout << "\tsem filhos a esquerda...\n";
        }
        if(no->direita){
            std::cout << "\tFilho direita: " << no->direita->aluno_info.nome << std::endl;
        }else{
            std::cout << "\tsem filhos a direita...\n";
        }
        mostrarArvore2(no->direita);
    }
}

tipoNo *buscarAlunoAux(tipoNo *no, std::string nomeAluno){
    if(!no or !no->aluno_info.nome.compare(nomeAluno)){
        return no;
    }
    if(nomeAluno.compare(no->aluno_info.nome) < 0){
        return buscarAlunoAux(no->esquerda, nomeAluno);
    }else{
        return buscarAlunoAux(no->direita, nomeAluno);
    }
}

tipoNo *buscarAlunoAux2(tipoNo *no, std::string nomeAluno){
    while(no){
        if(!no->aluno_info.nome.compare(nomeAluno)){
            return no;
        }else if(nomeAluno.compare(no->aluno_info.nome) < 0){
            no = no->esquerda;
        }else{
            no = no->direita;
        }
    }
    return NULL;
}

void buscarAluno(tipoArvore *arvore, std::string nomeAluno){
    tipoNo *aux = buscarAlunoAux2(arvore->raiz, nomeAluno);
    if(aux){
        std::cout << "[SUCESSO] aluno " << nomeAluno << " encontrado!" << std::endl;
    }else{
        std::cout << "[ERRO] aluno " << nomeAluno << " nao encontrado..." << std::endl;
    }
}

tipoNo *menorNo(tipoNo *no){
    while(no->esquerda){
        no = no->esquerda;
    }
    return no;
}

void transplante(tipoArvore *arvore, tipoNo *u, tipoNo *v){
    if(!u->pai){
        arvore->raiz = v;
    }else if(u == u->pai->esquerda){
        u->pai->esquerda = v;
    }else{
        u->pai->direita = v;
    }
    if(v){
        v->pai = u->pai;
    }
}

void deletarAluno(tipoArvore *arvore, std::string nomeAluno){
    tipoNo *z = buscarAlunoAux2(arvore->raiz, nomeAluno);
    if(z){
        if(!z->esquerda){
            transplante(arvore, z, z->direita);
        }else if(!z->direita){
            transplante(arvore, z, z->esquerda);
        }else{
            tipoNo *y = menorNo(z->direita);
            if(y != z->direita){
                transplante(arvore, y, y->direita);
                y->direita = z->direita;
                y->direita->pai = y;
            }
            transplante(arvore, z, y);
            y->esquerda = z->esquerda;
            y->esquerda->pai = y;
        }
        arvore->numNos--;
        std::string nome = z->aluno_info.nome;
        delete(z);
        std::cout << nome << " foi deletado!" << std::endl;
    }else{
        std::cout << "Nenhum aluno com nome " << nomeAluno << " para ser deletado..." << std::endl;
    }
}

int main(){
    tipoArvore arvore;
    iniciarArvore(&arvore);
    tipoAluno aluno;

    aluno.nome = "Daniel Silva";
    aluno.idade = 25;
    aluno.matricula = "02456789800";
    aluno.coeficiente = 8.494;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Lorena Leao";
    aluno.idade = 21;
    aluno.matricula = "01334599601";
    aluno.coeficiente = 6.364;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Amanda Loid";
    aluno.idade = 27;
    aluno.matricula = "03177732199";
    aluno.coeficiente = 9.331;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Thiago Botelha";
    aluno.idade = 23;
    aluno.matricula = "02283897719";
    aluno.coeficiente = 7.468;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Maria do Carmo";
    aluno.idade = 28;
    aluno.matricula = "00758583899";
    aluno.coeficiente = 5.355;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Rogerio Lima";
    aluno.idade = 20;
    aluno.matricula = "07237368901";
    aluno.coeficiente = 8.221;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Geraldo Pereira";
    aluno.idade = 19;
    aluno.matricula = "03356678720";
    aluno.coeficiente = 6.261;
    inserirAluno(&arvore, aluno);

    aluno.nome = "Carolina dos Santos";
    aluno.idade = 22;
    aluno.matricula = "04455512119";
    aluno.coeficiente = 7.334;
    inserirAluno(&arvore, aluno);
    
    mostrarArvore2(arvore.raiz);

    buscarAluno(&arvore, "Geraldo Pereira");
    buscarAluno(&arvore, "Pedro");

    deletarAluno(&arvore, "Oliver");
    deletarAluno(&arvore, "Rogerio Lima");

    mostrarArvore2(arvore.raiz);
}
