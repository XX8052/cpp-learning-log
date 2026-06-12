# C++ File Saving Notes

This note records what I learned about file saving and loading in C++.

## 1. Core Idea

In my program, data is stored in a `vector`.

```cpp
vector<Libraryarea> libraryareas;
```

This data is stored in memory.
When the program exits, the data will disappear.

File saving means:

```text
memory data -> text file
```

File loading means:

```text
text file -> memory data
```

So the program can keep data even after it closes.

---

## 2. `cin`, `cout`, `fin`, and `fout`

My understanding:

```text
cin  -> input from keyboard
cout -> output to screen
fin  -> input from file
fout -> output to file
```

They are all stream objects.

```cpp
cin >> data;    // read from keyboard
cout << data;   // write to screen

fin >> data;    // read from file
fout << data;   // write to file
```

Key point:

```text
cin / cout are for console input and output.
fin / fout are for file input and output.
```

---

## 3. Header File

To use file input and output, I need:

```cpp
#include <fstream>
```

`fstream` provides file stream tools.

Common file stream objects:

```cpp
ofstream fout;  // file output stream
ifstream fin;   // file input stream
```

---

## 4. What Is `fout`?

```cpp
ofstream fout("library_areas_information.txt");
```

This creates a file output object named `fout`.

It opens the file:

```text
library_areas_information.txt
```

Then I can write data into the file:

```cpp
fout << "Reading Room" << endl;
```

This is similar to:

```cpp
cout << "Reading Room" << endl;
```

Difference:

```text
cout writes to the screen.
fout writes to a file.
```

---

## 5. Saving One Object

Because the member variables are private, I cannot directly access them outside the class.

```cpp
private:
    string name;
    int floor;
    string location;
    string description;
```

So I let each object save its own data.

```cpp
void saveToFile(ofstream& fout) const {
    fout << name << endl;
    fout << floor << endl;
    fout << location << endl;
    fout << description << endl;
}
```

Key point:

```text
Each object writes its own data to the file.
```

`ofstream& fout` means the file output stream is passed by reference.

English note:

```text
Pass fout by reference because file streams should not be copied.
```

---

## 6. Saving the Whole Vector

One object can save itself, but the whole `vector` needs another function.

```cpp
void saveareas(const vector<Libraryarea>& libraryareas){
    ofstream fout("library_areas_information.txt");

    if(!fout){
        cout << "Failed to open file." << endl;
        return;
    }

    fout << libraryareas.size() << endl;

    for(int i = 0; i < libraryareas.size(); i++){
        libraryareas[i].saveToFile(fout);
    }

    fout.close();

    cout << "Data saved successfully." << endl;
}
```

Function responsibility:

```text
saveareas()   -> saves the whole vector
saveToFile()  -> saves one Libraryarea object
```

---

## 7. Will Saving Repeat Old Data?

No.

This line:

```cpp
ofstream fout("library_areas_information.txt");
```

opens the file in overwrite mode by default.

That means:

```text
old file content is cleared first
new data is written again
```

So the data will not keep stacking.

Only this mode will append data:

```cpp
ofstream fout("library_areas_information.txt", ios::app);
```

`ios::app` means append mode.

For my project, I should not use append mode.

---

## 8. Why Save `libraryareas.size()` First?

The first line of the file stores how many objects there are.

```cpp
fout << libraryareas.size() << endl;
```

Example saved file:

```text
3
Reading Room
1
East Area
Quiet study area
Computer Books
3
North Area
Programming and CS books
Discussion Room
4
South Area
Group study and discussion
```

The first line:

```text
3
```

means there are 3 library areas.

Then every 4 lines represent one object:

```text
name
floor
location
description
```

This makes loading easier.

---

## 9. Loading Data from File

Loading is the opposite of saving.

```text
read count
loop count times
read name, floor, location, description
create object
push object into vector
```

Code:

```cpp
void loadareas(vector<Libraryarea>& libraryareas){
    ifstream fin("library_areas_information.txt");

    if(!fin){
        cout << "No saved file found. Use default data." << endl;
        return;
    }

    int count;
    fin >> count;
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
```

---

## 10. Why Use `fin.ignore()`?

`fin >> count` reads the number, but it leaves the newline character.

Example file:

```text
3
Reading Room
```

After:

```cpp
fin >> count;
```

The number `3` is read, but the newline after `3` is still there.

If I directly use:

```cpp
getline(fin, name);
```

`getline` may read the leftover newline as an empty line.

So I need:

```cpp
fin.ignore(numeric_limits<streamsize>::max(), '\n');
```

Key point:

```text
After using fin >> number, clear the leftover newline before getline.
```

This is the same idea as `cin.ignore()`.

```text
cin.ignore() clears keyboard input stream.
fin.ignore() clears file input stream.
```

---

## 11. Why Use `libraryareas.clear()`?

Before loading saved data, I should clear old vector data.

```cpp
libraryareas.clear();
```

Reason:

```text
If I do not clear the vector, old data and loaded data may be mixed together.
```

For example:

```text
default data + file data
```

This may create duplicate records.

English note:

```text
clear() removes old vector data before loading saved data.
```

---

## 12. How to Use in `main()`

A good structure:

```cpp
int main(){
    vector<Libraryarea> libraryareas;

    loadareas(libraryareas);

    if(libraryareas.empty()){
        Setdefault(libraryareas);
    }

    // menu loop
}
```

Meaning:

```text
Try to load data from file first.
If there is no saved data, use default data.
```

---

## 13. Key Mistakes I Met

### Mistake 1: Wrong file opening syntax

Wrong:

```cpp
ofstream fout("");"library_areas_information.txt";
```

Correct:

```cpp
ofstream fout("library_areas_information.txt");
```

English note:

```text
The file name should be passed directly to the ofstream constructor.
```

---

### Mistake 2: Forgetting `<fstream>`

If I use `ofstream` or `ifstream`, I need:

```cpp
#include <fstream>
```

English note:

```text
ofstream and ifstream are provided by the fstream header.
```

---

### Mistake 3: Forgetting `fin.ignore()`

After reading a number from the file, I need to clear the leftover newline before using `getline`.

```cpp
fin >> floor;
fin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(fin, location);
```

English note:

```text
fin >> reads the number but leaves the newline in the file stream.
```

---

## 14. Final Summary

File saving is not magic.

It is just changing the data direction:

```text
cout -> output to screen
fout -> output to file

cin  -> input from keyboard
fin  -> input from file
```

The main idea:

```text
Save:
vector -> file

Load:
file -> vector
```

The most important rule:

```text
Use fout to write data.
Use fin to read data.
Use ignore() after reading numbers before getline().
```
