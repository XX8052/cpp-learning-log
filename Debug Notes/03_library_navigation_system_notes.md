# Debug Notes: Library Navigation System

This note records the small problems I met while building the Library Navigation System.

## 1. Passing Vector by Value

### Problem

I first passed the vector without `&`.

```cpp
void Setdefault(vector<Libraryarea> libraryareas)
```

### Key Point

The function only modified a copy of the vector, not the original vector in `main()`.

### Fix

```cpp
void Setdefault(vector<Libraryarea>& libraryareas)
```

Use reference when a function needs to modify the original vector.

---

## 2. Creating Objects with Real Data

### Problem

I mixed parameter declarations with real data when creating objects.

### Wrong Idea

```cpp
Libraryarea(string Reading Room, int 1, string East Area, string description)
```

### Key Point

Types are only needed when defining parameters.
When creating an object, only real values are needed.

### Fix

```cpp
Libraryarea("Reading Room", 1, "East Area", "Quiet study area")
```

---

## 3. Reading Strings with Spaces

### Problem

`cin >> name` cannot read strings with spaces.

For example:

```text
Reading Room
```

`cin >> name` only reads:

```text
Reading
```

### Fix

```cpp
getline(cin, name);
```

`getline` reads the whole line, including spaces.

---

## 4. Leftover Newline after `cin >>`

### Problem

After using `cin >>`, the Enter key remains in the input buffer.

Then `getline` may read that leftover newline as an empty line.

### Fix

```cpp
cin.ignore(numeric_limits<streamsize>::max(), '\n');
```

This clears the rest of the current input line.

---

## 5. Do Not Clear Input after Every `getline`

### Problem

I called `cin.ignore()` before or after too many `getline` operations.

### Key Point

`getline` already reads the current line.
Calling `ignore()` at the wrong time may discard the next valid input.

### Rule

```text
Use cin.ignore() after cin >>, not after every getline.
```

---

## 6. Empty String Is Not a `cin` Failure

### Problem

When the user pressed Enter directly, `getline` read an empty string.

This is not a `cin` error.

### Key Point

```cpp
getline(cin, text);
```

can successfully read an empty line.

### Fix

Check the string itself:

```cpp
if (text.empty()) {
    cout << "invalid information";
}
```

---

## 7. Spaces Are Not an Empty String

### Problem

If the user enters only spaces, `text.empty()` does not detect it.

```text
"   "
```

This is not empty because it contains spaces.

### Fix

Check whether the string only contains whitespace.

```cpp
bool isBlank(const string& s) {
    return s.find_first_not_of(" \t\r\n") == string::npos;
}
```

---

## 8. `cin` Failed State

### Problem

If `cin >> intValue` tries to read text, `cin` enters a failed state.

After that, later input operations may stop working correctly.

### Fix

```cpp
cin.clear();
cin.ignore(numeric_limits<streamsize>::max(), '\n');
```

`cin.clear()` resets the error state.
`cin.ignore()` removes the invalid input.

---

## 9. Missing Function Call Parentheses

### Problem

I wrote:

```cpp
cleandata;
```

### Key Point

This does not call the function.

### Fix

```cpp
cleandata();
```

Function calls need parentheses.

---

## 10. Menu Input Validation

### Problem

The program should reject invalid menu choices.

### Fix

```cpp
if (choice < 1 || choice > 6) {
    cout << "invalid information";
}
```

`||` means OR.

---

## 11. Clear Prompts Matter

### Problem

The prompt looked like one-line input:

```text
enter name floor location description to add
```

But the program actually read the data step by step.

### Better Design

```text
Name:
Floor:
Location:
Description:
```

Clear prompts make input easier and reduce mistakes.

---

## What I Learned

* Use reference when modifying the original vector.
* Use `getline` for strings with spaces.
* Clear leftover newline after `cin >>`.
* Do not use `cin.ignore()` randomly.
* Empty string and failed input are different problems.
* Validate important numeric input.
* Clear input prompts are part of good program design.
