#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Bankaccount{
private:
    string name;
    int accountid;
    double property;
    bool verify(int id){
        if(accountid==id){
            return true;
        }
    }
public:
    Bankaccount(string n,int a,double p){
        name=n;
        accountid=a;
        property=p;
    }
    void addmoney(vector<Bankaccount>& bankaccounts,int id,int add){
        for(int i=0;i<bankaccounts.size();i++){
            if(bankaccounts[i].verify(id)) {
                bankaccounts[i].property+=add;
            }
        }
    }
    void takemoney(vector<Bankaccount>& bankaccounts,int id,int add){
        for(int i=0;i<bankaccounts.size();i++){
            if(bankaccounts[i].verify(id)) {
                bankaccounts[i].property-=add;
            }
        }
    }
    void show(vector<Bankaccount>& bankaccounts,int id){
        for(int i=0;i<bankaccounts.size();i++){
            if(bankaccounts[i].verify(id)) {
                cout<<name<<"  "<<accountid<<"  "<<property<<"  ";
            }
        }
    }
};
void addaccount(vector<Bankaccount>& bankaccounts){
    string name;
    int accountid;
    double property;
    cout<<"please enter: name  accountid  property";
    cin>>name>>accountid>>property;
    bankaccounts.push_back(Bankaccount(name,accountid,property));

}
int main(){
    vector<Bankaccount> bankaccounts;
    int choice;
    cout<<endl<<"choose your intention"<<endl;
    cout<<"1 add acconts"<<endl<<"2 deposit"<<endl<<"3 take"<<endl<<"4 showaccounts"<<endl<<"else break the syestem";
    while(true){
        cin>>choice;
        if(choice==1){
            addaccount(bankaccounts);
        }
        else if(choice==2){
            int id;
            int money;
            cout<<"please enter id money";
            cin>>id>>money;
            bankaccounts[0].addmoney(bankaccounts,id,money);
        }
        else if(choice==3){
            int id;
            int money;
            cout<<"please enter id money";
            cin>>id>>money;
            bankaccounts[0].takemoney(bankaccounts,id,money);
        }
        else if(choice==4){
            int id;
            cout<<"enter your accountid";
            cin>>id;
            bankaccounts[0].show(bankaccounts,id);
        }
        else{
            break;
        }
        cout<<endl<<"what next";
    }
    return 0;
}
