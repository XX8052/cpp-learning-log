#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

class Libraryarea {
   private:
    string name;
    int floor;
    string location;
    string description;

   public:
    Libraryarea(string n, int f, string l, string d) {
        name = n;
        floor = f;
        location = l;
        description = d;
    }

    bool matchname(const string& n) const {
        return name == n;
    }

    bool matchfloor(const int& f) const {
        return f == floor;
    }

    bool matchlocation(const string& l) const {
        return l == location;
    }

    void show() const {
        cout << endl
             << "Name  " << name << endl
             << "Floor  " << floor << "F" << endl
             << "Location  " << location << endl
             << "Description  " << description << endl;
    }

    void showname() const {
        cout << "   " << name << endl;
    }

    void saveToFile(ofstream& fout) const {
        fout << name << endl;
        fout << floor << endl;
        fout << location << endl;
        fout << description << endl;
    }
};

bool isBlank(const string& s) {
    return s.find_first_not_of(" \t\r\n") == string::npos;
}

void cleandata() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void cinint(int& n) {  // verify the cin "int" data
    while (true) {
        if (!(cin >> n)) {
            cout << "invalid information" << endl << "please retry" << endl;
            cin.clear();
            cleandata();
        }

        else {
            cleandata();
            break;
        }
    }
}

void cinstring(string& n) {
    while (true) {
        getline(cin, n);

        if (!isBlank(n)) {
            break;
        }

        cout << "invalid information" << endl;
        cout << "please retry" << endl;
    }
}

void showMenu() {
    cout << endl;
    cout << "===== Library Navigation System =====" << endl;
    cout << "    1. Show all areas" << endl;
    cout << "    2. Search area by name" << endl;
    cout << "    3. Search area by floor" << endl;
    cout << "    4. Show area details" << endl;
    cout << "    5.Add area information" << endl;
    cout << "    6. Save data" << endl;
    cout << "    7. Exit" << endl;
    cout << "input your choice: ";
}

void showMenuwrong() {
    cout << endl;
    cout << "===== Library Navigation System =====" << endl;
    cout << "    1. Show all areas" << endl;
    cout << "    2. Search area by name" << endl;
    cout << "    3. Search area by floor" << endl;
    cout << "    4. Show area details" << endl;
    cout << "    5.Add area information" << endl;
    cout << "    6. Save data" << endl;
    cout << "    7. Exit" << endl;
    cout << "make sure your input is valid: ";
}

void setDefaultAreas(vector<Libraryarea>& libraryareas) {
    libraryareas.push_back(Libraryarea("Reading Room", 1, " East Area", "Quiet study area"));
    libraryareas.push_back(Libraryarea("Borrowing Desk", 1, "Main Hall", "Borrow and return books"));
    libraryareas.push_back(Libraryarea("Computer Books", 3, "North Area", "Programming and CS books"));
    libraryareas.push_back(Libraryarea("Printing Ar ea", 2, "Near Exit", "Printing and copying service·"));
    libraryareas.push_back(Libraryarea("Discussion Room", 4, "South Area", "Group study and discussion"));
}

void saveareas(const vector<Libraryarea>& libraryareas) {
    ofstream fout("04_library_areas_information.txt");

    if (!fout) {
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

void loadareas(vector<Libraryarea>& libraryareas) {
    ifstream fin("04_library_areas_information.txt");

    if (!fin) {
        cout << "No saved file found. Use default data." << endl;
        return;
    }

    int count;
    fin >> count;  // know the type of data
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    libraryareas.clear();

    for (int i = 0; i < count; i++) {
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

void pauseScreen() {
    cout << endl;
    cout << "Press Enter to continue...";
    cin.get();
}

void searchName(vector<Libraryarea>& Libraryareas) {
    bool found = 0;
    cout << "enter the name:";
    string name;
    cinstring(name);

    for (int i = 0; i < Libraryareas.size(); i++) {
        if (Libraryareas[i].matchname(name)) {
            Libraryareas[i].show();
            found = 1;
            pauseScreen();
            break;
        }

        if (!found) {
            cout << "No area found with this name." << endl;
            pauseScreen();
        }
    }
}

void searchFloor(vector<Libraryarea>& Libraryareas) {
    bool found = 0;
    cout << "enter the floor:";
    int floor;
    cinint(floor);
    for (int i = 0; i < Libraryareas.size(); i++) {
        if (Libraryareas[i].matchfloor(floor)) {
            Libraryareas[i].show();
            found = 1;
        }

        if (found) {
            pauseScreen();
        }

        if (!found) {
            cout << "No area found with this floor." << endl;
            pauseScreen();
        }
    }
}

int main() {
    vector<Libraryarea> Libraryareas;
    setDefaultAreas(Libraryareas);
    int choice;
    loadareas(Libraryareas);
    showMenu();

    while (true) {
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid information,please retry";
            showMenuwrong();
            continue;
        }

        cleandata();

        if (choice < 1 || choice > 7) {
            cout << "invalid information";
            continue;
        }

        if (choice == 1) {
            cout << endl << "====Area Information====" << endl;
            for (int i = 0; i < Libraryareas.size(); i++) {
                Libraryareas[i].showname();
            }
            pauseScreen();
        }

        else if (choice == 2) {
            searchName(Libraryareas);
        }

        else if (choice == 3) {
            searchFloor(Libraryareas);
        }

        else if (choice == 4) {
            for (int i = 0; i < Libraryareas.size(); i++) {
                Libraryareas[i].show();
            }

            pauseScreen();
        }

        else if (choice == 5) {
            cout << "enter name floor location discription to add" << endl;
            string n;
            int f;
            string l;
            string d;
            cout << "Name: ";
            cinstring(n);
            cout << "Floor: ";
            cinint(f);
            cout << "Location: ";
            cinstring(l);
            cout << "Description: ";
            cinstring(d);
            Libraryareas.push_back(Libraryarea(n, f, l, d));
            cout << "store successfully";
            pauseScreen();
        }

        else if (choice == 6) {
            saveareas(Libraryareas);
            pauseScreen();
        }

        else {
            cout << "exit successfully";
            break;
        }

        cout << endl << "choose to continue" << endl;
    }
    return 0;
}