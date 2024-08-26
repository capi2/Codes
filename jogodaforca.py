import random

def mostrar_matriz(m):
    for i in range(0,len(m)):
        for j in range(0,len(m[0])):
            print(m[i][j],end=" ")
        print("\n") 

def ler_arquivo():
    #le um arquivo de texto .txt para criar uma lista de palavras
    arquivo = open("palavras.txt", "r")
    lista_palavras = []
    for linha in arquivo:
        linha = linha.strip()
        lista_palavras.append(linha)
    arquivo.close()
    return lista_palavras

def sortear_palavra():
    lista_palavras = ler_arquivo()
    num_aleatorio = random.choice(range(0,len(lista_palavras)))
    return lista_palavras[num_aleatorio]

def criar_forca():
    #cria a matriz com a forca posicionada
    m = [[" "," "," "," "," "," "],[" "," "," "," "," "," "],[" "," "," "," "," "," "],[" "," "," "," "," "," "],[" "," "," "," "," "," "],[" "," "," "," "," "," "]]   
    for i in range(0,len(m)):
        m[i][0] = "|"
    for j in range(1,len(m[0])-3):
        m[0][j] = "-"
    m[0][int(len(m[0])/2)] = "|"
    return m

def jogo_da_forca():
    #funcao principal que inicia o jogo da forca, le a matriz e sorteia uma palavra para comecar
    print("Vamos jogar o jogo da forca?")
    matriz = criar_forca()

    palavra = sortear_palavra()
    resposta = list("_"*len(palavra))

    tentativa = 7
    while(tentativa > 0):
        letra = input("Digite uma letra: ")
        letra = letra.lower()
        if letra not in palavra:
            print("[ERRO] Letra nao existe na palavra!\n")
            if tentativa == 7:
                matriz[1][3] = "Ô"
                mostrar_matriz(matriz)
            elif tentativa == 6:
                matriz[2][3] = "|"
                mostrar_matriz(matriz)
            elif tentativa == 5:
                matriz[2][2] = "/"
                mostrar_matriz(matriz)
            elif tentativa == 4:
                matriz[2][4] = "\."
                mostrar_matriz(matriz)
            elif tentativa == 3:
                matriz[3][3] = "|"
                mostrar_matriz(matriz)
            elif tentativa == 2:
                matriz[4][2] = "/"
                mostrar_matriz(matriz)
            elif tentativa == 1:
                matriz[4][4] = "\."
                mostrar_matriz(matriz)
                print("Voce perdeu...")
                print(["GAME OVER"])
            tentativa -= 1
        else:
            for i in range(0,len(palavra)):
                if palavra[i] == letra:
                    resposta[i] = letra
            print("Palavra resultante das letras informadas ate entao...")
            for i in resposta:
                print(i,end="")
            print("\n\nSituacao da forca...\n")
            mostrar_matriz(matriz)
        if "_" not in resposta:
            print("Parabens, voce adivinhou a palavra!")
            print("[GAME OVER]")
            break

if(__name__ == "__main__"):
    jogo_da_forca()