#Organizacao dos Computadores - Montador v1.1
#Discente: Andre Kaoru Lins Hirosaki
#Matricula: 22251133

#ATT.1 - Montador com as funcoes HALT e MOVE RA,RB implementadas

import sys

def converter_binario_para_hexa(instrucao):
    res = ""
    res += binario_hex[instrucao[:4]]
    res += binario_hex[instrucao[4:]]
    return res

def ignorar_ponto_e_virgula(instrucao):
    index_ponto_e_virgula = instrucao.find(';')
    
    if index_ponto_e_virgula != -1:
        instrucao = instrucao[:index_ponto_e_virgula]
    
    return instrucao

lista_comandos = {
    "add":"1000",
    "shr":"1001",
    "shl":"1010",
    "not":"1011",
    "and":"1100",
    "or":"1101",
    "xor":"1110",
    "cmp":"1111",
    "ld":"0000",
    "st":"0001",
    "data":"001000",
    "jmpr":"001100",
    "jmp":"01000000",
    "jc":"01011000",
    "ja":"01010100",
    "je":"01010010",
    "jz":"01010001",
    "jca":"01011100",
    "jce":"01011010",
    "jcz":"01011001",
    "jae":"01010110",
    "jaz":"01010101",
    "jez":"01010011",
    "jcae":"01011110",
    "jcaz":"01011101",
    "jcez":"01011011",
    "jaez":"01010111",
    "jcaez":"01011111",
    "clf":"01100000",
    "r0":"00",
    "r1":"01",
    "r2":"10",
    "r3":"11",
    "in":"01110",
    "out":"01111"
}

binario_hex = {
    "0000":"0",
    "0001":"1",
    "0010":"2",
    "0011":"3",
    "0100":"4",
    "0101":"5",
    "0110":"6",
    "0111":"7",
    "1000":"8",
    "1001":"9",
    "1010":"a",
    "1011":"b",
    "1100":"c",
    "1101":"d",
    "1110":"e",
    "1111":"f"
}

def read_inputfile(input_file):
    comandos = []
    with open(input_file, "r") as f:
        while True:
            linha = f.readline()
            if not linha:
                break
            linha = linha.replace(',',' ')
            linha = linha.lower()
            linha = ignorar_ponto_e_virgula(linha)
            if "move" in linha:
                linha = linha.split()
                comandos.append("xor " + linha[2] + " " + linha[2])
                comandos.append("add " + linha[1] + " " + linha[2])
                comandos.append("xor " + linha[1] + " " + linha[1])
            else:
                if not linha.startswith((".code", ".data")):
                    comandos.append(linha.strip())
            
    cd = [i for i in comandos if i]
    return cd

def converter_comandos(comandos):
    cd = []
    for i in range(0,len(comandos)):
        instrucao = comandos[i].split(" ")
        inst = ""
        if "data" in instrucao[0]:
            if "0x" in instrucao[2]:
                instrucao[2] = instrucao[2].replace("0x", "")
            elif "0b" in instrucao[2]:
                instrucao[2] = instrucao[2].replace("0b","")
                instrucao[2] = converter_binario_para_hexa(instrucao[2])
            else:
                if int(instrucao[2]) < 16:
                    instrucao[2] = hex(int(instrucao[2]))
                    instrucao[2] = instrucao[2].replace("0x", "0")
                else:
                    instrucao[2] = hex(int(instrucao[2]))
                    instrucao[2] = instrucao[2].replace("0x", "")
            inst = lista_comandos[instrucao[0]] + lista_comandos[instrucao[1]]
            cd.append(converter_binario_para_hexa(inst))
            if(instrucao[2] in ['0','1','2','3','4','5','6','7','8','9']):
                cd.append("0"+instrucao[2])
            else:
                cd.append(instrucao[2])
        elif instrucao[0] in ["jmp", "jc", "ja", "je", "jz", "jca", "jce", "jcz", "jae", "jaz", "jez", "jcae", "jcaz", "jcez", "jaez", "jcaez"]:
            if "0x" in instrucao[1]:
                instrucao[1] = instrucao[1].replace("0x", "")
            elif "0b" in instrucao[1]:
                instrucao[1] = instrucao[1].replace("0b","")
                instrucao[1] = converter_binario_para_hexa(instrucao[1])
            else:
                if int(instrucao[1]) < 16:
                    instrucao[1] = hex(int(instrucao[1]))
                    instrucao[1] = instrucao[1].replace("0x", "0")
                else:
                    instrucao[1] = hex(int(instrucao[1]))
                    instrucao[1] = instrucao[1].replace("0x", "")
            inst = lista_comandos[instrucao[0]]
            cd.append(converter_binario_para_hexa(inst))
            cd.append(instrucao[1])
        else:
            if "word" in instrucao:
                if "0x" in instrucao[1]:
                    instrucao[1] = instrucao[1].replace("0x", "")
                elif "0b" in instrucao[1]:
                    instrucao[1] = instrucao[1].replace("0b","")
                    instrucao[1] = converter_binario_para_hexa(instrucao[1])
                else:
                    if int(instrucao[1]) < 16:
                        instrucao[1] = hex(int(instrucao[1]))
                        instrucao[1] = instrucao[1].replace("0x", "0")
                    else:
                        instrucao[1] = hex(int(instrucao[1]))
                        instrucao[1] = instrucao[1].replace("0x", "")
                cd.append(instrucao[1])
            elif "halt" in instrucao:
                inst = len(cd)
                inst = hex(inst)
                inst = inst.replace("0x", "")
                cd.append("40")
                if(inst in ['0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f']):
                    cd.append("0"+inst)
                else:
                    cd.append(inst)
            else:
                for j in range(0,len(instrucao)):
                    if instrucao[j] == "addr":
                        inst += "1"
                    elif instrucao[j] == "data":
                        inst += "0"
                    else:
                        inst += lista_comandos[instrucao[j]]
                cd.append(converter_binario_para_hexa(inst))
    return cd

def write_outputfile(memory_file, input_file):
    comandos = read_inputfile(input_file)
    comandos = converter_comandos(comandos)
    k = 0
    with open(memory_file, "w") as f:
        f.write('v3.0 hex words plain')
        for i in range(0,16):
            f.write('\n')
            for j in range(0,16):
                if(k < len(comandos)):
                    f.write(comandos[k]+' ')
                    k+=1
                else:
                    f.write("00 ")

def main(memory_file, input_file):
    write_outputfile(memory_file, input_file)

if __name__ == '__main__':
    n = len(sys.argv)
    assert n == 3, 'number argument erro'

    main(sys.argv[1], sys.argv[2])