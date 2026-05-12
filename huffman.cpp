#include <iostream>
#include <vector>
#include<map>
#include<queue>
using namespace std;

class No{
    public:
        char simbolo;
        int freq;
        No* esq;
        No* dir;
        No(int freq,char simbolo=' '){
            this->esq = nullptr;
            this->dir = nullptr;
            this->simbolo = simbolo;
            this->freq = freq;
        }
        void libera(No* no){
            if(!no)return;
            libera(no->esq);
            libera(no->esq);
            delete no;
        }
    
};

struct Cmp {
        bool operator()(No* a, No* b) {
            return a->freq > b->freq; 
        }
    };

class huffman{
    public:
        string palavra;
        string codificada;
        map<char,int>freq;
        map<char,string>tabela;
        priority_queue<No*,vector<No*>,Cmp>fila;
        No* raiz = new No(0);
        void calcula_freq(string s){
            for(char c : s)freq[c]++;
        }
        void gera_fila(){
            for(auto [c,f] : freq){
                fila.push(new No(f,c));
            }
        }
        void gera_arvore(){
            while(fila.size()>1){
                No* esq = fila.top();fila.pop();
                No* dir = fila.top();fila.pop();
                No* pai = new No(esq->freq+dir->freq);
                pai->esq = esq;
                pai->dir = dir;
                fila.push(pai);
            }
        }
        void gera_tabela(No* no,string prefixo){
            if(no == nullptr)return ;
            if(!no->esq && !no->dir){
                tabela[no->simbolo] = prefixo;
                return;
            }
            gera_tabela(no->esq,prefixo+"1");
            gera_tabela(no->dir,prefixo+"0");
        }

        huffman(string palavra){
            this->palavra = palavra;
            calcula_freq(palavra);
            gera_fila();
            gera_arvore();
            raiz = fila.top();
            gera_tabela(raiz,"");
        }

        string encode(){
            string saida = "";
            for(char c : palavra)saida += tabela[c];
            codificada = saida;
            return saida;
        }
        string decode(){
            string saida = "";
            No* atual = raiz;
            for(char b: codificada){
                if(b == '0') atual = atual->dir;
                else atual = atual->esq;
                if(!atual->esq && !atual->dir){
                    saida += atual->simbolo;
                    atual = raiz;
                }
            }return saida;
        }

        
        

};

int main() {
    string palavra = "banana";
    huffman hf(palavra);
    cout <<hf.encode()<<endl;
    cout <<hf.decode()<<endl;
    return 0;
}