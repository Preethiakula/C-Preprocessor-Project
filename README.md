# MY PREPROCESSOR - C Mini Project

A beginner-level C program that demonstrates basic preprocessing tasks using modular C source and header files.

## Features

- Removes single-line (`//`) and multi-line (`/* ... */`) comments while preserving quoted text.
- Includes local header files using `#include "file.h"` and `#include <file.h>` when the file is available in the project/include path handled by this program.
- Supports object-like macros, for example `#define PI 3.14`.
- Supports simple one-argument function-like macros, for example `#define DOUBLE(x) ((x) + (x))` and `#define SQUARE(x) ((x) * (x))`.
- Uses modular programming with separate `.c` and `.h` files.
- Uses a Makefile to build the executable.
- Accepts an input `.c` filename as a command-line argument and creates a matching `.i` output file.

## Project files

- `main.c` - command-line handling and output-file creation.
- `preprocessor.c`, `preprocessor.h` - preprocessing flow and shared definitions.
- `comment_removal.c`, `comment_removal.h` - comment removal.
- `macro_handler.c`, `macro_handler.h` - macro definition and replacement.
- `file_inclusion.c`, `file_inclusion.h` - local header-file inclusion.
- `myheader.h` - sample header containing the `DOUBLE(x)` macro and helper function.
- `inputfile.c` - sample input used to test the project.
- `Makefile` - compilation rules.

## Build

Run these commands in the project directory:

```sh
make clean
make
```

## Run

```sh
./mypreprocessor inputfile.c
```

The program creates `inputfile.i` in the same directory. View it with:

```sh
cat inputfile.i
```

To compile and run the generated C output as an additional check:

```sh
gcc -x c inputfile.i -o test
./test
echo $?
```

An exit status of `0` means the sample test passed.

## Limitations

This is an educational mini-preprocessor, not a complete replacement for the standard C preprocessor. Function-like macros are limited to a single argument. Full macro rules, conditional compilation (`#if`, `#ifdef`, etc.), and standard system-header processing are not implemented.
