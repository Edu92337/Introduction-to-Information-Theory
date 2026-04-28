#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

string compress_string(string &s){
    string new_s = "";
    int i = 1;
    int t = 1;
    while(i<s.size()){
        if(s[i]==s[i-1])t++;
        else{
            if(t>1) new_s += to_string(t);
            new_s += s[i-1];
            t=1;
        }
        i++;
    }
    if(t > 1) new_s += to_string(t);
    new_s += s[s.size()-1];
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
    new_file.close();
    ifstream orig("rle_text.txt", ios::ate | ios::binary);
    ifstream comp("compressed_text.txt", ios::ate | ios::binary);
    cout << "Original:   " << orig.tellg() << " bytes" << endl;
    cout << "Comprimido: " << comp.tellg() << " bytes" << endl;
    cout <<"Fator de compressão : "<<float(comp.tellg())/orig.tellg() *100<<" %"<<endl;
    return 0;
}