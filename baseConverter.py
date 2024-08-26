#dados iniciais de valor, base de origem e base de destino fornecidos pelo usuario
valor = input("Digite um valor: ")
base_origem = input("Digite a base de origem: ")
base_destino = input("Digite a base de destino: ")

#alfabeto de simbolos
alfabeto = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
            "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

#valores correspondentes dos simbolos do alfabeto
valores = {"A":10, "B":11, "C":12, "D":13, "E":14, "F":15, "G":16, "H":17, "I":18,
           "J":19, "K":20, "L":21, "M":22, "N":23, "O":24, "P":25, "Q":26, "R":27,
           "S":28, "T":29, "U":30, "V":31, "W":32, "X":33, "Y":34, "Z":35}

#se uma base de origem nao for informada, considera a mesma como sendo 10
if base_origem == "":
    base_origem = 10

#se uma base de destino nao for informada, considera a mesma como sendo 10
if base_destino == "":
    base_destino = 10

#converte da base de origem especificada para base decimal
#primeiro checa se o valor inicial possui letras
#converte o valor da letra, se existente, e multiplica pela base de origem elevada a potencia correspondente
#em caso contrario, faz a operacao normalmente e guarda os valores em uma variavel acumuladora
def converter_base_decimal(n):
    valor_convertido = 0
    j = len(str(n))
    for i in str(n):
        if i.upper() in alfabeto:
            valor_convertido += valores[i.upper()]* int(base_origem)**(j-1)
            j-=1
        else:
            valor_convertido += int(i) * int(base_origem)**(j-1)
            j-=1
    return valor_convertido

#converte da base decimal para a base especificada
#primeiro realiza as divisoes sucessivas para a base especificada
#checa se o resto da divisao esta no intervalo de simbolos possiveis para conversao de valores
#concatena o resultado em uma variavel acumuladora e continua realizando a divisao inteira do valor
#somente quando o valor se torna menor que a base desejada o laco eh encerrado
#caso o valor ainda tenha um simbolo correspondente, retorna o simbolo
#em caso contrario, concatena o resultado a variavel e devolve o resultado final ao contrario
def converter_decimal_base(n):
    valor_convertido = ""
    while int(n) >= int(base_destino):
        if int(n)%int(base_destino) in range(10, 36):
            valor_convertido += alfabeto[int(n)%int(base_destino)-10]
            n = int(n) // int(base_destino)
        else:
            valor_convertido += str(int(n)%int(base_destino))
            n = int(n) // int(base_destino)
    if int(n) < int(base_destino):
        if int(n) < 10:
            valor_convertido += str(n)
        else:
            valor_convertido += alfabeto[n-10]
    return valor_convertido[::-1]

#funcao principal que converte o valor inicial fornecido entre as bases dadas
#primeiro converte o valor inicial para a base decimal para depois converter da base decimal para a base desejada
def converter(n):
    n = converter_base_decimal(n)
    return converter_decimal_base(n)

print("O valor inicial " + valor + " na base inicial " + base_origem +" convertido para a base " + base_destino + " vale " + converter(valor))

#######################################
# Discente: Andre Kaoru Lins Hirosaki #
# Matricula: 22251133                 #
#######################################
