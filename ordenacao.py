vet = [4,1,9,34,-1,0,99,342,45,87,11,-6]

def insertion_sort(vetor):
    for j in range(1,len(vetor)):
        chave = vetor[j]
        i = j - 1
        while(i >= 0 and vetor[i] > chave):
            vetor[i+1] = vetor[i]
            i -= 1
        vetor[i+1] = chave

def bubble_sort(vetor):
    for i in range(0,len(vetor)):
        for j in range(len(vetor)-1,i,-1):
            if(vetor[j] < vetor[j-1]):
                aux = vetor[j]
                vetor[j] = vetor[j-1]
                vetor[j-1] = aux

def merge(vetor, inicio, meio, fim):
    n1 = meio - inicio + 1
    n2 = fim - meio
    L = [0]*(n1)
    R = [0]*(n2)
    for i in range(0,n1):
        L[i] = vetor[inicio+i]
    for j in range(0,n2):
        R[j] = vetor[meio + j + 1]
    i = 0
    j = 0
    k = inicio
    while(i < n1 and j < n2):
        if(L[i] <= R[j]):
            vetor[k] = L[i]
            i += 1
        else:
            vetor[k] = R[j]
            j += 1
        k += 1
    while i < n1:
        vetor[k] = L[i]
        i += 1
        k += 1
    while j < n2:
        vetor[k] = R[j]
        j += 1
        k += 1

def merge_sort(vetor, inicio, fim):
    if inicio >= fim:
        return
    meio = (inicio + fim)//2
    merge_sort(vetor, inicio, meio)
    merge_sort(vetor, meio+1, fim)
    merge(vetor, inicio, meio, fim)

def particao(vetor, inicio, fim):
    x = vetor[fim]
    i = inicio - 1
    for j in range(inicio, fim):
        if(vetor[j] <= x):
            i += 1
            aux1 = vetor[i]
            vetor[i] = vetor[j]
            vetor[j] = aux1
    aux2 = vetor[i+1]
    vetor[i+1] = vetor[fim]
    vetor[fim] = aux2
    return i + 1

def quick_sort(vetor, inicio, fim):
    if inicio < fim:
        meio = particao(vetor, inicio, fim)
        quick_sort(vetor, inicio, meio - 1)
        quick_sort(vetor, meio + 1, fim)

def stooge_sort(vetor, inicio, fim):
    if(vetor[inicio] > vetor[fim]):
        aux = vetor[inicio]
        vetor[inicio] = vetor[fim]
        vetor[fim] = aux
    if(inicio + 1 < fim):
        k = (fim - inicio + 1)//3
        stooge_sort(vetor, inicio, fim-k)
        stooge_sort(vetor, inicio + k, fim)
        stooge_sort(vetor, inicio, fim-k)

#insertion_sort(vet)
#bubble_sort(vet)
#merge_sort(vet,0,len(vet)-1)
#quick_sort(vet, 0, len(vet) - 1)
stooge_sort(vet, 0, len(vet)-1)

print(vet)
