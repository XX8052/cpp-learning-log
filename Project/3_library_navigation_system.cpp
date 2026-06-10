#include<iostream>
#include<vector>
#include<string>
using namespace std;
class Libraryarea{
private:
    string name;
    int floor;
    string location;
    string description;
public:
    Libraryarea(string n,int f,string l,string d){
        name=n;
        floor=f;
        location=l;
        description=d;
    }
    bool matchname(string n){
        return name==n;
    }
    bool matchfloor(int f){
        return f==floor;
    }
    bool matchlocation(string l){
        return l==location;
    }
    bool matchdescription(string d){
        return d==description;
    }
    void show(){
        cout<<"name  "<<name<<"Floor  "<<floor<<"F  "<<"location  "<<location<<"description  "<<description<<endl;
    }
    void showname(){
        cout<<name<<endl;
    }
};
void showMenu() {
    cout << endl;
    cout << "===== Library Navigation System =====" << endl;
    cout << "1. Show all areas" << endl;
    cout << "2. Search area by name" << endl;
    cout << "3. Search area by floor" << endl;
    cout << "4. Show area details" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose: ";
}

void Setdefault(vector<Libraryarea>& libraryareas){      //& must be used,otherwise the function receives a copy of the variable, so the original value is not modified.
    libraryareas.push_back(Libraryarea( "Reading Room", 1," East Area","Quiet study area"));//just data,type is not needed
    libraryareas.push_back(Libraryarea( "Borrowing Desk", 1," Main Hall","Borrow and return books"));
    libraryareas.push_back(Libraryarea( "Computer Books", 3," North Area","Programming and CS books"));
    libraryareas.push_back(Libraryarea( "Printing Area ", 2,"  Near Exit","Public restroom"));
    libraryareas.push_back(Libraryarea( "Discussion Room ", 4," South Area","Group study and discussion"));
}
    
int main(){
    vector<Libraryarea> libraryareas;
    Setdefault(libraryareas);
    int choice;
    showMenu();
    while(true){
        cin>>choice;
        if(choice==1){
            for(int i=0;i<libraryareas.size();i++){
                libraryareas[i].showname();
            }
         }
        else if(choice==2){
            cout<<"enter the name:";
            string name;
            cin>>name;
            for(int i=0;i<libraryareas.size();i++){
                if(libraryareas[i].matchname(name)){
                    libraryareas[i].show();
                    break;
                }
            }
        }
        else if(choice==3){
            cout<<"enter the floor:";
            int floor;
            cin>>floor;
            for(int i=0;i<libraryareas.size();i++){
                if(libraryareas[i].matchfloor(floor)){
                libraryareas[i].show();
                break;
                }
            }
        }
        else if(choice==4){
            for(int i=0;i<libraryareas.size();i++){
                libraryareas[i].show();
            }
        }
        else if(choice==5){
            break;
        }
        cout<<endl<<"choose to continue";
    }

    return 0;
}
