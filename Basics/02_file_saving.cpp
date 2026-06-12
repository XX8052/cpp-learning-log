#include<iostream>
#include<fstream>
using namespace std;
int main(){
    cout<<"enter 2 numbers"<<endl;
    int a;
    int b;
    string c;
    cin>>a>>b;
    ofstream fout("file_saving.txt");
    ifstream fin("file_saving.txt");
    fout<<a<<endl;
    fout<<b<<endl;
    fout.close();
    cout<<"press a to check data researved"<<endl;
    cin>>c;
    ifstream fin("file_saving.txt");
    if(c=="a"){
        fin>>a;
        fin>>b;
        cout<<a<<endl<<b<<endl;
        fin.close();
    }
}
