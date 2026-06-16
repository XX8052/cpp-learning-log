# Debug Notes: C++ Header Files and Multi-file Compilation

This note records the basic idea of `.h` files, `.cpp` files, and how to compile multiple C++ files with `g++`.

## 1. What Is a `.h` File?

`.h` means **header file**.

A `.h` file is still a normal text file, but it is usually used to store declarations.

### Key Point

```text
.h file = declaration / interface / what the code has
.cpp file = implementation / how the code works
```

In simple words:

```text
.h tells other files what exists.
.cpp writes how those things actually work.
```

---

## 2. Example File Structure

A basic multi-file C++ project can look like this:

```text
Libraryarea.h
Libraryarea.cpp
main.cpp
```

### Meaning

```text
Libraryarea.h      Class declaration
Libraryarea.cpp    Function implementation
main.cpp           Main program logic
```

---

## 3. `Libraryarea.h`

The header file declares the class.

```cpp
#ifndef LIBRARYAREA_H
#define LIBRARYAREA_H

#include <string>
#include <fstream>
using namespace std;

class Libraryarea {
private:
    string name;
    int floor;
    string location;
    string description;

public:
    Libraryarea(string n, int f, string l, string d);

    bool matchname(string n) const;
    bool matchfloor(int f) const;

    void show() const;
    void saveToFile(ofstream& fout) const;
};

#endif
```

### Key Point

The `.h` file does not usually write the full function body.

It mainly tells other files:

```text
This class exists.
These member variables exist.
These member functions exist.
```

---

## 4. `Libraryarea.cpp`

The `.cpp` file writes the actual function code.

```cpp
#include "Libraryarea.h"
#include <iostream>
using namespace std;

Libraryarea::Libraryarea(string n, int f, string l, string d) {
    name = n;
    floor = f;
    location = l;
    description = d;
}

bool Libraryarea::matchname(string n) const {
    return name == n;
}

bool Libraryarea::matchfloor(int f) const {
    return floor == f;
}

void Libraryarea::show() const {
    cout << "Name: " << name
         << " Floor: " << floor
         << " Location: " << location
         << " Description: " << description << endl;
}

void Libraryarea::saveToFile(ofstream& fout) const {
    fout << name << endl;
    fout << floor << endl;
    fout << location << endl;
    fout << description << endl;
}
```

### Key Point

```cpp
Libraryarea::show()
```

means:

```text
The show function belongs to the Libraryarea class.
```

`::` is the scope resolution operator.

---

## 5. `main.cpp`

The main file uses the class.

```cpp
#include <iostream>
#include <vector>
#include "Libraryarea.h"
using namespace std;

int main() {
    vector<Libraryarea> libraryareas;

    libraryareas.push_back(
        Libraryarea("Reading Room", 1, "East Area", "Quiet study area")
    );

    libraryareas[0].show();

    return 0;
}
```

### Key Point

```cpp
#include "Libraryarea.h"
```

means:

```text
main.cpp needs to know the declaration of Libraryarea.
```

---

## 6. Do We Compile `.h` Files Directly?

Usually, no.

Wrong idea:

```bash
g++ Libraryarea.h
```

Correct idea:

```bash
g++ main.cpp Libraryarea.cpp -o library_system
```

The `.h` file is included by `.cpp` files through:

```cpp
#include "Libraryarea.h"
```

---

## 7. How to Understand This Command?

```bash
g++ main.cpp Libraryarea.cpp -o library_system
```

### Translation

```text
Use g++ to compile main.cpp and Libraryarea.cpp,
then output an executable program named library_system.
```

### Breakdown

```text
g++                 Use the g++ compiler
main.cpp            Compile main.cpp
Libraryarea.cpp     Compile Libraryarea.cpp
-o                  Output
library_system      Name of the final executable program
```

### Memory Rule

```text
g++ source1.cpp source2.cpp -o output_name
```

Example:

```bash
g++ main.cpp Libraryarea.cpp -o library_system
```

---

## 8. Why Multiple `.cpp` Files?

When a project gets bigger, putting everything in one file becomes messy.

Multi-file structure helps separate code clearly.

```text
.h      tells what exists
.cpp    writes how it works
main    controls the program flow
```

This makes the project easier to read, maintain, and expand.

---

## 9. Common Mistakes

### Mistake 1: Forgetting to include the header file

```cpp
#include "Libraryarea.h"
```

Without this, `main.cpp` may not know what `Libraryarea` is.

### Mistake 2: Compiling only `main.cpp`

Wrong:

```bash
g++ main.cpp -o library_system
```

If `Libraryarea.cpp` contains function implementations, this may cause linker errors.

Correct:

```bash
g++ main.cpp Libraryarea.cpp -o library_system
```

### Mistake 3: Thinking `.h` is a special document format

`.h` is just a text file that stores C++ declarations.

---

## 10. What I Learned

* `.h` means header file.
* `.h` usually stores declarations.
* `.cpp` stores actual function implementations.
* `main.cpp` controls the main program logic.
* `#include "Libraryarea.h"` lets one file know the declarations from another file.
* `g++ main.cpp Libraryarea.cpp -o library_system` compiles multiple source files into one executable program.
* `-o` means output.
* Multi-file structure makes C++ projects cleaner and easier to maintain.
