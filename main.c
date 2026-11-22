#include "preprocessor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    Preprocessor p;
    char *result;
    char output_name[300];
    int length;
    FILE *output_file;

    if (argc != 2)
    {
        printf("Usage: ./mypreprocessor inputfile.c\n");
        return 1;
    }

    length = (int)strlen(argv[1]);
    if (length < 3 || strcmp(argv[1] + length - 2, ".c") != 0)
    {
        printf("Please give a .c file\n");
        return 1;
    }

    initialize_preprocessor(&p);
    result = preprocess_file(&p, argv[1]);
    free_preprocessor(&p);
    if (result == NULL)
    {
        printf("Preprocessing failed\n");
        return 1;
    }

    strcpy(output_name, argv[1]);
    output_name[length - 1] = 'i';
    output_file = fopen(output_name, "w");
    if (output_file == NULL)
    {
        perror(output_name);
        free(result);
        return 1;
    }

    fputs(result, output_file);
    fclose(output_file);
    printf("Preprocessing completed\n");
    printf("Output file: %s\n", output_name);
    free(result);
    return 0;
}
