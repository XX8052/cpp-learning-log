#include<iostream>
#include<string>
#include<vector>
#include <limits>
using namespace std;

class Bankaccount{
private:
    string name;
    int accountid;
    double property;
public:
    bool verify(int id){
        return id==accountid;
    }
    Bankaccount(string n,int a,double p){
        name=n;
        accountid=a;
        property=p;
    }
    void addmoney(int add){
        if (add > 0) {
            property += add;
            cout << "Deposit successful." << endl;
        }
        else {
            cout << "Invalid amount." << endl;
        }
    }
    void takemoney(int take){
        if (take <= 0) {
            cout << "Invalid amount." << endl;
        }
        else if (take > property) {
            cout << "Not enough balance." << endl;
        }
        else{
            property-=take;
            cout << "Withdrawal successful." << endl;
        }
    }
    void show(){
        cout<<"Name:  "<<name<<"  Account Id:  "<<accountid<<"  Balance:  "<<property<<endl;
        cout << "searching successful." << endl;
    }
};

void addaccount(vector<Bankaccount>& bankaccounts){
    string name;
    int accountid;
    double property;
    cout<<"Bank Account Deposite System"<<endl<<"please enter:your name  accountid  property"<<endl;
    cin>>name>>accountid>>property;
    if(property>0){
        bankaccounts.push_back(Bankaccount(name,accountid,property));
        cout<<"Command executed successfully"<<endl;
    }
    else{
        cout<<"invalid data";
    }
}
void pauseScreen() {
    cout<< endl<<"Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

int main(){
    vector<Bankaccount> bankaccounts;
    int choice;
    while(true){
        cout<<endl<<"choose your intention"<<endl;
        cout<<"1 add acconts"<<endl<<"2 deposit"<<endl<<"3 take"<<endl<<"4 showaccounts"<<endl<<"else break the syestem"<<endl;
        cin>>choice;
        if(choice==1){
            addaccount(bankaccounts);
            pauseScreen();
        }
        else if(choice==2){
            int id;
            double money;
            cout<<endl<<"Bank Account Deposite System"<<endl<<"please enter your account id and money"<<endl;
            cin>>id>>money;
            for(int i=0;i<bankaccounts.size();i++){
                if(bankaccounts[i].verify(id)){
                    bankaccounts[i].addmoney(money);
                    pauseScreen();
                    break;
                }

            }
        }
        else if(choice==3){
            int id;
            double money;
            cout<<endl<<"Bank Account Withdrawal System"<<endl<<"please enter your account id and money"<<endl;
            cin>>id>>money;
            for(int i=0;i<bankaccounts.size();i++){
                if(bankaccounts[i].verify(id)){
                    bankaccounts[i].takemoney(money);
                    pauseScreen();
                    break;
                }
            }
        }
        else if(choice==4){
            int id;
            cout<<endl<<"Bank Account Showing System"<<endl<<"please enter your account id "<<endl;
            cin>>id;
            bool found=false;
            for(int i=0;i<bankaccounts.size();i++){
                if(bankaccounts[i].verify(id)){
                    bankaccounts[i].show();
                    pauseScreen();
                    bool found = true;
                    break;
                }
            }
            if(!found){
                cout << "Account not found" << endl;
            }
        }
        else{
            cout<<endl<<"System exits successfully";
            break;
        }
    }
    return 0;
}

