#include<iostream>
#include<vector>

using namespace std;

/*
10
presentation
preserve
president
press
pressure
prestige
prestigious
pretty
prevent
previous

*/
int real_size(vector<string>&vec){
    int t = 0;
    for(string s: vec)t += s.size()*sizeof(char);
    return t;
}

pair<int,int> find_number(string s){
    string number = "";
    int i = 0;
    int n = s.size();
    while(i<n && isdigit(s[i])){
        number+=s[i];
        i++;
    }
    return {stoi(number),number.size()};
}

int first_carac(string a,string b){
    int t = min(a.size(),b.size());
    int i = 0;
    while(i<t && a[i]==b[i]){
        i++;
    }
    return i;
}
void compress_ds(vector<string>&vec){
    //front compression
    int n = vec.size();
    vector<int>qnt(n,0);

    for(int i = 1;i<vec.size();i++){
        int t = first_carac(vec[i],vec[i-1]);
        if(t!=0){
            qnt[i] = t;
        }
    }
    for(int i = 0;i<n;i++){
        if(qnt[i]!= 0) vec[i] = to_string(qnt[i]) + vec[i].substr(qnt[i]);
    }

}

void decompress_ds(vector<string>&compressed_vec){
    int n = compressed_vec.size();
    for(int i =1;i<n;i++){
        auto [t,p] = find_number(compressed_vec[i]);
        compressed_vec[i] = compressed_vec[i-1].substr(0,t) + compressed_vec[i].substr(p);

    }

}

int main(){
    int n;cin >> n;
    float t0,tf;
    vector<string> vec(n);

    for(int i = 0;i<n;i++){
        cin >> vec[i];
    }
    t0 = real_size(vec);
    cout <<"Tamanho original : "<<t0<<" Bytes"<<endl;
    compress_ds(vec);
    tf = real_size(vec);
    cout <<"Tamanho comprimido : "<<tf<<" Bytes"<<endl;
    for(string s:vec)cout <<s<<" ";
    cout <<endl;
    cout<<"Porcentagem comprimida: "<<tf/t0 *100<<"%"<<endl;
    cout <<"Voltando para o original: ";
    decompress_ds(vec);
    for(auto s:vec) cout <<s<<" ";
    cout <<endl;



    return 0;
}