#include <iostream>

class Livro{
    public:
        std::string nome;
        std::string autor;
        std::string descrever();
        Livro(std::string nome_livro, std::string autor_nome);
};

Livro::Livro(std::string nome_livro, std::string autor_nome){
    nome = nome_livro;
    autor = autor_nome;
}

std::string Livro::descrever(){
    return "O nome deste livro eh " + nome + " e o seu autor se chama " + autor;
}

int main(){
    Livro livro("O Lamento das Ondas", "Carlos Jose");
    std::cout << livro.descrever() << std::endl;
    int num = 234;
    std::cout << std::to_string(num) << std::endl;
}