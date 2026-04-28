#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


//aaabbcc -> 3a2b2c
string compress_string(string &s){
    string new_s = "";
    int i = 1;
    int t = 1;
    while(i<s.size()){
        if(s[i]==s[i-1])t++;
        else{
            new_s += to_string(t);
            new_s += s[i-1];
            t=1;
        }
        i++;
    }
    return new_s;

}



int main() {

    ifstream arquivo("rle_text.txt");
    ofstream new_file("compressed_text.txt");
    string palavra;
    if(arquivo.is_open()){
        while(arquivo >> palavra){
            string new_s = compress_string(palavra);
            new_file << new_s<<" ";
        }
    }
    return 0;
}