#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// convert string to camel case
// string must be separated by '-' or '_'
void to_camel_case(const char *text, char *camel) {
    int i = 0;
    strcpy(camel, text);
    int tam = strlen(camel);
    while(camel[i]){
        if(camel[i] == '-' || camel[i] == '_'){
            if(camel[i+1] >= 97 && camel[0] <= 122){
                camel[i+1] -= 32;
            }
            int j = i+1;
            int k = i;
            while(k < tam){
                camel[k] = camel[j];
                j++;
                k++;
            }
        }
        i++;
    }
    printf("%s\n", camel);
}


// verify if string has only upper case letters, then returns true
// otherwise returns false
bool is_uppercase(const char *source){
  int tam = strlen(source);
  for(int i = 0; i < tam; i++){
    if(source[i] >= 97 && source[i] <= 122){
        printf("%c\n", source[i]);
      return false;
    }
  }
  return true;
}

// given an array, find integer with odd occurences in array
// only one number will appear odd times
int find_odd (size_t length, const int array[length]){
    int num;
    for(size_t i = 0; i < length; i++){
        num = array[i];
        int occur = 1;
        for(size_t j = 0; j < length; j++){
            if(i != j && num == array[j]){
            occur++;
            }
        }
        if(occur%2 != 0){
            return array[i];
        }
    }
}

// tribonacci receives an signature array with starting numbers
// instead of two, but three numbers are used to calculate tribonacci sequence
long long *tribonacci(const long long signature[3], size_t n){
    long long *ans = malloc(sizeof(long) * n);
    if(!ans || n == 0){
        return NULL;
    }else{
        for(int i = 0; i < 3; i++){
            ans[i] = signature[i];
        }
        for(size_t j = 3; j < n; j++){
            ans[j] = ans[j-1] + ans[j-2] + ans[j-3];
        }
        return ans;
    }
}

// calculates how many times the digits inside the number must be multiplied until a single digit number occurs
// example: 39 return 3 because 3*9 = 27, 2*7 = 14 and 1*4 = 4. That's 3 times the number's digits were multiplied
int multiply_digits(int num){
    if (num < 10){
        return num;
    }else{
        return num%10*multiply_digits(num/10);
    }
}

int persistence(int n) {
    char aux[15];
    sprintf(aux, "%d", n);
    int cont = 0;
    while(strlen(aux) != 1){
        n = multiply_digits(n);
        sprintf(aux, "%d", n);
        cont++;
    }
    return cont;
}

int main(){
    int num = 4;
    printf("%d\n", persistence(num));
}