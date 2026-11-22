#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#define MAX_MACROS 100
#define MAX_NAME 50
#define MAX_VALUE 200
#define MAX_FILE 100000
#define MAX_DEPTH 10

typedef struct
{
    char name[MAX_NAME];
    char value[MAX_VALUE];
    char parameter[MAX_NAME];
    int is_function;
} Macro;

typedef struct
{
    Macro macros[MAX_MACROS];
    int macro_count;
    char *active_files[MAX_DEPTH];
    int depth;
} Preprocessor;

void initialize_preprocessor(Preprocessor *p);
void free_preprocessor(Preprocessor *p);
char *preprocess_file(Preprocessor *p, const char *file_name);

#endif
