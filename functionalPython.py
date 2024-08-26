import numpy as np

def listSize(some_list):
    if not some_list:
        return 0
    else:
        return 1 + listSize(some_list[1:])
    
def listSum(some_list):
    if not some_list:
        return 0
    else:
        return some_list[0] + listSum(some_list[1:])
    
def factorial(number):
    if number == 0 or number == 1:
        return 1
    else:
        return number * factorial(number -1)

def isPrime(number):
    if number == 0 or number == 1:
        return False
    else:
        for i in range(2,number):
            if number%i == 0:
                return False
        return True
    
def isEven(number):
    if number%2 == 0:
        return True
    else:
        return False

def applyFunction(function, number):
    return function(number)

def myMap(function, some_list):
    if not some_list:
        return []
    else:
        return [applyFunction(function, some_list[0])] + myMap(function, some_list[1:])
    
def myFilter(function, some_list):
    if not some_list:
        return []
    else:
        result = function(some_list[0])
        if(result):
            return [some_list[0]] + myFilter(function, some_list[1:])
        else:
            return myFilter(function, some_list[1:])
        
def pipeline(number, functionList):
    if not functionList:
        return number
    else:
        return pipeline(functionList[0](number), functionList[1:])
    
def reverse(some_list):
    if not some_list:
        return []
    else:
        return reverse(some_list[1:]) + [some_list[0]]

def isPalindrome(some_list):
    if some_list == reverse(some_list):
        return True
    else:
        return False

def isMember(number, some_list):
    if not some_list:
        return False
    else:
        if number == some_list[0]:
            return True
        else:
            return isMember(number, some_list[1:])

def maximumValue(some_list):
    if not some_list:
        return 0
    elif len(some_list) == 1:
        return some_list[0]
    else:
        maior = some_list[0]
        if maior < some_list[1]:
            return maximumValue(some_list[1:])
        else:
            return maximumValue([some_list[0]] + some_list[2:])

def minimumValue(some_list):
    if not some_list:
        return 0
    elif len(some_list) == 1:
        return some_list[0]
    else:
        menor = some_list[0]
        if menor > some_list[1]:
            return minimumValue(some_list[1:])
        else:
            return minimumValue([some_list[0]] + some_list[2:])

def isOrderedCrescent(some_list):
    if not some_list or len(some_list) == 1:
        return True
    else:
        if some_list[0] > some_list[1]:
            return False
        else:
            return isOrderedCrescent(some_list[1:])
        
def isOrderedDecrescent(some_list):
    if not some_list or len(some_list) == 1:
        return True
    else:
        if some_list[0] < some_list[1]:
            return False
        else:
            return isOrderedDecrescent(some_list[1:])

#testing
print(listSize([1,7,2,9,4,6,0]))
print(listSum([1,2,3,4,5]))
print([factorial(x) for x in range(10)])
print(myMap(lambda x: np.sqrt(x), range(10)))
print(myFilter(isPrime, range(20)))
print(myFilter(isEven, range(25)))
print(pipeline(4, [lambda x: x+11, lambda x: np.sqrt(x), lambda x: x/7]))
print(reverse([4,9,1,2,0]))
print(isPalindrome([1,3,2,3,1]))
print(isPalindrome([5,8,2,3]))
print(isMember(3,[9,4,8,3,0]))
print(isMember(9, [4,1,7]))
print(maximumValue([5,2,9,0,1]))
print(minimumValue([3,8,5,1,0]))
print(isOrderedCrescent([4,7,2,9,1]))
print(isOrderedCrescent([1,3,6,8,9]))
print(isOrderedDecrescent([3,7,1,0,4]))
print(isOrderedDecrescent([8,4,2,1,0]))