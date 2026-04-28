#include<iostream>
#include<vector>

using namespace std;

int real_size(vector<string>&vec){
    int t = 0;
    for(string s: vec)t += s.size()*sizeof(char);
    return t;
}

void compress(vector<string>&vec){
    for(int i = vec.size()-1;i>0;i--){
        int dif = stoi(vec[i]) - stoi(vec[i-1]);
        vec[i] = to_string(dif);
        
    }
}


void decompress(vector<string>&vec){
    for(int i = 1;i<vec.size();i++){
        vec[i] = to_string(stoi(vec[i])+stoi(vec[i-1]));
    }
}

int main(){
    int n; cin>>n;
    vector<string>nums(n);
    float t0,tf;
    for(int i = 0;i<n;i++)cin >> nums[i];
    t0 = real_size(nums);
    cout <<"Tamanho original : "<< t0<<endl;
    compress(nums);
    tf = real_size(nums);
    cout <<"Tamanho final :"<< tf<<endl;
    cout<<"Porcentagem comprimida : "<<tf/t0 *100<<"%"<<endl;
    decompress(nums);
    for(string x:nums)cout <<x <<" ";
    cout <<endl;


    return 0;
}