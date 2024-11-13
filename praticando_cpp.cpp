#include <iostream>
#include <string>
#include <bits/stdc++.h>

// returns the length of the shortest word in string
int find_short(std::string str){
    std::stringstream ss(str);
    std::string word;
    ss >> word;
    int short_string_length = word.length(); 
    while(ss >> word){
        if(word.length() < short_string_length){
            short_string_length = word.length();
        }
    }
    return short_string_length;
}
