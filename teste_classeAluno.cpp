#include <iostream>

class Aluno{
    public:
        std::string nome;
        unsigned idade;
        void descrever();
        void gritar();
        void tabuada(int num);
        Aluno(std::string nomeAluno, unsigned idade, std::string cpfAluno);
        std::string getCpf(){
            return cpf;
        }
        std::string getNome(){
            return nome;
        }
        int getIdade(){
            return idade;
        }
        void falarSobreVida(){
            std::cout << "Tenho " << idade << " anos mas ainda tenho um longo caminho pela frente!" << std::endl;
        }
        std::string refletir();
    private:
        std::string cpf;
};

Aluno::Aluno(std::string nomeAluno, unsigned idadeAluno, std::string cpfAluno){
    nome = nomeAluno;
    idade = idadeAluno;
    cpf = cpfAluno;
}

void Aluno::gritar(){
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAH" << std::endl;
}

void Aluno::descrever(){
    std::cout << "Oi, meu nome eh " << Aluno::getNome() << " e tenho " << Aluno::getIdade() << " anos!" << std::endl;
}

void Aluno::tabuada(int num){
    std::cout << "Estou dizendo a tabuada do " << num << std::endl;
    for(int i = 1; i <= 10; i++){
        std::cout << num << " * " << i << " = " << num*i << std::endl;
    }
}

std::string Aluno::refletir(){
    return "Puxa vida, quantos " + Aluno::nome + " sera que existem por ai...?";
}

int main(){
    Aluno al1("Maria Santos", 20, "03165499901");
    al1.gritar();
    al1.tabuada(8);
    //std::cout << al1.cpf << std::endl; nao funciona por ser private!
    std::cout << al1.getCpf() << std::endl;

    al1.descrever();

    al1.falarSobreVida();

    Aluno al2("Joao Silva", 25, "04455673201");
    al2.tabuada(4);
    al2.descrever();
    al2.falarSobreVida();
    std::cout << al2.refletir() << std::endl;
}