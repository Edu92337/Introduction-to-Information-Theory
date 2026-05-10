#include <iostream>
#include <vector>
#include<map>
#include<queue>

using namespace std;

void calcula_freq(string s, map<char,int>&freq){
    for(char c : s)freq[c]++;
}

struct No {
    int freq;
    char simbolo;
    No* esq;
    No* dir;
};


struct Cmp {
    bool operator()(No* a, No* b) {
        return a->freq > b->freq; // min-heap
    }
};

void libera(No* no){
    if(!no) return;
    libera(no->esq);
    libera(no->dir);
    delete no;
}



void gera_tabela(map<char,string>&tabela,No* no,string prefixo){
    if(no ==nullptr){
        return;
    }
    if(!no->esq && !no->dir){
        tabela[no->simbolo] = prefixo;
        return;
    }
    gera_tabela(tabela,no->esq,prefixo+"0");
    gera_tabela(tabela,no->dir,prefixo + "1");

}


string codifica(string texto,map<char,string>&tabela){
    string saida = "";
    for(char c: texto) saida += tabela[c];
    return saida;
}

string decodifica(string code,No* raiz){
    string saida = "";
    No* atual = raiz;
    for(char b : code){
        if(b=='0')atual = atual->esq;
        else atual = atual->dir;
        if(!atual->esq && !atual->dir){
            saida += atual->simbolo;
            atual = raiz;
        }
    }
    return saida;
}

int main() {
    map<char,int>freq;
    map<char,string>tabela;
    string palavra = "banana";

    priority_queue<No*, vector<No*>, Cmp> heap;
    calcula_freq(palavra,freq);
    for(auto [c, f] : freq){
        No* no = new No();
        no->freq = f;
        no->simbolo = c;
        no->esq = nullptr;
        no->dir = nullptr;
        heap.push(no);
    }

    //construir a arvore

    while(heap.size()>1){
        No* esq = heap.top();
        heap.pop();
        No* dir = heap.top();
        heap.pop();
        No* pai = new No();
        
        pai->freq = esq->freq + dir->freq;
        pai->esq = esq;
        pai->dir = dir;

        heap.push(pai);
    }
    No* raiz = heap.top(); 
    gera_tabela(tabela,raiz,"");
    string codificada = codifica(palavra,tabela);
    cout <<codificada<<endl;
    string decodificada = decodifica(codificada,raiz);
    cout << decodificada<<endl;
    libera(raiz);
    return 0;
}