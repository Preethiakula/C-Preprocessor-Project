#include "preprocessor.h"
#include "comment_removal.h"
#include "macro_handler.h"
#include "file_inclusion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void add_line(char *output, const char *line)
{
    if (strlen(output) + strlen(line) < MAX_FILE - 2)
        strcat(output, line);
}

void initialize_preprocessor(Preprocessor *p)
{
    p->macro_count = 0;
    p->depth = 0;
}

void free_preprocessor(Preprocessor *p)
{
    (void)p;
}

char *preprocess_file(Preprocessor *p, const char *file_name)
{
    FILE *file;
    char *source;
    char *output;
    char line[2000];
    char clean_line[2000];
    char include_name[200];
    char include_path[500];
    int i;

    if (p->depth >= MAX_DEPTH) return NULL;
    for (i = 0; i < p->depth; i++)
        if (strcmp(p->active_files[i], file_name) == 0) return NULL;

    file = fopen(file_name, "r");
    if (file == NULL)
    {
        perror(file_name);
        return NULL;
    }

    source = malloc(MAX_FILE);
    output = malloc(MAX_FILE);
    if (source == NULL || output == NULL)
    {
        fclose(file);
        free(source);
        free(output);
        return NULL;
    }
    source[0] = '\0';
    output[0] = '\0';

    while (fgets(line, sizeof(line), file) != NULL)
        add_line(source, line);
    fclose(file);

    remove_comments(source);
    p->active_files[p->depth] = malloc(strlen(file_name) + 1);
    if (p->active_files[p->depth] == NULL)
    {
        free(source);
        free(output);
        return NULL;
    }
    strcpy(p->active_files[p->depth], file_name);
    p->depth++;

    {
        char *line_start = source;
        while (*line_start != '\0')
        {
            char *end = strchr(line_start, '\n');
            int length;
            if (end != NULL) length = (int)(end - line_start) + 1;
            else length = (int)strlen(line_start);
            if (length >= (int)sizeof(line)) length = (int)sizeof(line) - 1;
            strncpy(line, line_start, length);
            line[length] = '\0';
            line_start += length;

            strcpy(clean_line, line);
            i = 0;
            while (clean_line[i] == ' ' || clean_line[i] == '\t') i++;

            if (clean_line[i] == '#' && strncmp(clean_line + i, "#define", 7) == 0)
            {
                add_macro(p, clean_line + i + 7);
            }
            else if (clean_line[i] == '#' && strncmp(clean_line + i, "#include", 8) == 0)
            {
                if (get_include_name(clean_line + i + 8, include_name))
                {
                    char *included_text;
                    make_include_path(file_name, include_name, include_path);
                    included_text = preprocess_file(p, include_path);
                    if (included_text != NULL)
                    {
                        add_line(output, included_text);
                        free(included_text);
                    }
                }
            }
            else
            {
                char expanded[2000];
                replace_macros(p, clean_line, expanded);
                add_line(output, expanded);
            }
        }
    }

    p->depth--;
    free(p->active_files[p->depth]);
    free(source);
    return output;
}
