# `Toolkit.c` — Documentation

The `Toolkit` module provides an interface for working with external utilities (GCC, Python, nano) within the user file system `UserFiles`.

---

## Functions

### `void toolkit_gcc(const char *args)`

Compiles a C file using GCC. Automatically adds the `UserFiles/` path before the source and output files (if `-o` is specified).

#### Parameters:

* `args` — a string with the source file and additional compilation options (for example: `test.c -o test`).

#### Features:

* Support for output redirection to `UserFiles/`.
* If successful, reports successful compilation, otherwise reports an error.

#### Example call:

```c
toolkit_gcc("main.c -o main");
```

---

### `void toolkit_python(const char *filename)`

Runs a Python script from the `UserFiles` directory.

#### Parameters:

* `filename` — the name of the Python script to run (for example: `script.py`).

#### Example call:

```c
toolkit_python("script.py");
```

---

### `void toolkit_nano(const char *filename)`

Opens a file in the `nano` text editor from the `UserFiles` directory.

#### Parameters:

* `filename` — the name of the file to edit (for example: `notes.txt`).

#### Example call:

```c
toolkit_nano("notes.txt");
```

---

## Dependencies

* External programs: `gcc`, `python`, `nano`
* Access to the `UserFiles/` folder
