#include<iostream>
#include<vector>
#include<string>
#include<limits>
#include <fstream>
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
    void show(){
        cout<<"name  "<<name<<"  Floor  "<<floor<<"F  "<<"location  "<<location<<"  description  "<<description<<endl;
    }
    void showname(){
        cout<<name<<endl;
    }
    void saveToFile(ofstream& fout) const {
        fout << name << endl;
        fout << floor << endl;
        fout << location << endl;
        fout << description << endl;
    }
};

bool isBlank(const string& s){
    return s.find_first_not_of(" \t\r\n") == string::npos;
}
void cleandata(){                                           //clean useless \n. <>declare the data type ::declare scope
     cin.ignore(numeric_limits<streamsize>::max(), '\n');     //numeric_limits template tools
}
void cinint(int &n){                //verify the cin "int" data
    while(true){
        if(!(cin>>n)){
            cout<<"invalid information"<<endl<<"please retry"<<endl;
            cin.clear();
            cleandata();
        }
        else{
            cleandata();
            break;
        }
    }
}
void cinstring(string &n){              //verify the string data
    while(true){
        getline(cin,n);
        if(n.empty()||isBlank(n)){
            cout<<"invalid information"<<endl<<"please retry"<<endl;
            cin.clear();            //onle ignore after cin;
        }
        else{
            break;
        }
    }
}
void showMenu() {
    cout << endl;
    cout << "===== Library Navigation System =====" << endl;
    cout << "1. Show all areas" << endl;
    cout << "2. Search area by name" << endl;
    cout << "3. Search area by floor" << endl;
    cout << "4. Show area details" << endl;
    cout<<"5.Add area information"<<endl;
    cout << "6. Save data" << endl;
    cout << "7. Exit" << endl;
    cout << "Choose: ";
}

void Setdefault(vector<Libraryarea>& libraryareas){         //& must be used,otherwise the function receives a copy of the variable, so the original value is not modified.
    libraryareas.push_back(Libraryarea( "Reading Room", 1," East Area","Quiet study area"));//just data,type is not needed
    libraryareas.push_back(Libraryarea( "Borrowing Desk", 1,"Main Hall","Borrow and return books"));
    libraryareas.push_back(Libraryarea( "Computer Books", 3,"North Area","Programming and CS books"));
    libraryareas.push_back(Libraryarea( "Printing Area", 2,"Near Exit","Public restroom"));
    libraryareas.push_back(Libraryarea( "Discussion Room", 4,"South Area","Group study and discussion"));
}  
void saveareas(const vector<Libraryarea>& libraryareas){
    ofstream fout("04_library_areas_information.txt");             // ofstream opens the file in overwrite
    if(!fout){
        cout << "Failed to open file." << endl;
        return;
    }
    fout << libraryareas.size() << endl;
    for (int i = 0; i < libraryareas.size(); i++) {
        libraryareas[i].saveToFile(fout);
    }
    fout.close();
    cout << "Data saved successfully." << endl;
}
void loadareas(vector<Libraryarea>& libraryareas){
    ifstream fin("04_library_areas_information.txt");
    if(!fin){
        cout << "No saved file found. Use default data." << endl;
        return;
    }
    int count;
    fin >> count;                       //know the type of data
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    libraryareas.clear();
    for(int i = 0; i < count; i++){
        string name;
        int floor;
        string location;
        string description;
        getline(fin, name);
        fin >> floor;
        fin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(fin, location);
        getline(fin, description);
        libraryareas.push_back(Libraryarea(name, floor, location, description));
    }
    fin.close();
    cout << "Data loaded successfully." << endl;
}
int main(){
    vector<Libraryarea> libraryareas;
    Setdefault(libraryareas);
    int choice;
    showMenu();
    loadareas(libraryareas);
    while(true){
        if(!(cin>>choice)){                                         //instruction+condition verifying
            cin.clear();                                            //clear the wrong state;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');     //delete wrong data;
            cout<<"invalid information,please retry";                //make sure the cin is right;
            continue; 
        }
        else if(choice<1||choice>7){
            cout<<"invalid information";                       
            continue;
        }
        if(choice==1){
            cout<<"====Area Information===="<<endl;
            for(int i=0;i<libraryareas.size();i++){
                libraryareas[i].showname();
            }
         }
        else if(choice==2){
            cout<<"enter the name:";
            string name;
            cinstring(name);
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
            cinint(floor);
            for(int i=0;i<libraryareas.size();i++){
                if(libraryareas[i].matchfloor(floor)){
                libraryareas[i].show();
                }
            }
        }
        else if(choice==4){
            for(int i=0;i<libraryareas.size();i++){
                libraryareas[i].show();
            }
        }
        else if(choice==5){
            cout<<"enter name floor location discription to add"<<endl;
            string n;
            int f;
            string l;
            string d;
            cout << "Name: ";           
            cleandata();            //not press enter again!before input data! clean data before the code;not when instruct;
            cinstring(n);
            cout << "Floor: ";
            cinint(f);
            cout << "Location: ";
            cinstring(l);
            cout << "Description: ";
            cinstring(d);      
            libraryareas.push_back(Libraryarea(n,f,l,d));       
            cout<<"store successfully";         
        }
        else if(choice==6){
            saveareas(libraryareas);
        }
        else {
            break;
        }
        cout<<endl<<"choose to continue"<<endl;
    }
    return 0;
}
