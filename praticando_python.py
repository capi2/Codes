# function receives a list of integers and a number as input
# returns a list with integers whose occurence is less or equal than provided number
# example: [20,37,20,21] and 1 should return [20, 37, 21] because 20 happens 2 times
# example: [3,1,4,2,5,1,1] and 2 should return [3, 1, 4, 2, 5, 1] because 1 happens 3 times

def make_dictionary(lista):
    dic = {}
    for number in lista:
        if number not in dic:
            dic[number] = 0
    return dic

def check_list(lista, number):
    final_list = []
    dic = make_dictionary(lista)
    for item in lista:
        dic[item] += 1
        if dic[item] <= number:
            final_list.append(item)
    return final_list

print(check_list([3,1,4,2,5,1,1], 2))

# transforms the number to binary notation
# convert_to_binary calls transform_to_binary and add_pontuation for better binary representation
def transform_to_binary(numero):
    if numero == 0:
        return "0"
    elif numero == 1:
        return "1"
    else:
        if numero%2 == 0:
            return transform_to_binary(numero//2) + "0"
        else:
            return transform_to_binary(numero//2) + "1"

def add_pontuation(binary_string):
    if len(binary_string) == 4:
        return binary_string
    else:
        return binary_string[:4] + "." + add_pontuation(binary_string[4:])

def convert_to_binary(numero):
    res = transform_to_binary(numero)
    while(len(res)%4 != 0):
        res = "0" + res
    res = add_pontuation(res)
    return res

print(convert_to_binary(100))

# transforms the number to hexadecimal notation
# convert_to_hexadecimal calls convert_to_binary to help transforming the number
def convert_to_hexadecimal(numero):
    hex_dic = {10:"a", 11:"b", 12:"c", 13:"d", 14:"e", 15:"f"}
    bin = convert_to_binary(numero)
    sum = 0
    pos_value = 8
    hex_string = ""
    bits_read = 0
    for bit in bin:
        if bit == "1":
            sum += pos_value
            pos_value = pos_value//2
            bits_read += 1
        elif bit == "0":
            pos_value = pos_value//2
            bits_read += 1
        if bits_read == 4:
                if sum < 10:
                    hex_string += str(sum)
                else:
                    hex_string += hex_dic[sum]
                sum = 0
                pos_value = 8
                bits_read = 0
    return hex_string

print(convert_to_hexadecimal(23959))