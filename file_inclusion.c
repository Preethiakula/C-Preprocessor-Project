#include "file_inclusion.h"
#include <string.h>

int get_include_name(const char *line, char *file_name)
{
    int i = 0;
    int j = 0;
    char end_char;

    while (line[i] == ' ' || line[i] == '\t') i++;
    if (line[i] == '"') end_char = '"';
    else if (line[i] == '<') end_char = '>';
    else return 0;
    i++;

    while (line[i] != '\0' && line[i] != end_char && j < 199)
        file_name[j++] = line[i++];
    file_name[j] = '\0';

    return line[i] == end_char;
}

void make_include_path(const char *current_file, const char *include_name, char *full_path)
{
    const char *slash = strrchr(current_file, '/');
    if (slash == NULL)
    {
        strcpy(full_path, include_name);
    }
    else
    {
        int length = (int)(slash - current_file + 1);
        strncpy(full_path, current_file, length);
        full_path[length] = '\0';
        strcat(full_path, include_name);
    }
}
