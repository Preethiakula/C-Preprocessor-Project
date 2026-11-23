#include "macro_handler.h"
#include <stdio.h>
#include <string.h>

static int is_name_char(char ch)
{
    return isalnum((unsigned char)ch) || ch == '_';
}

static void add_text(char *result, int *position, const char *text)
{
    while (*text && *position < MAX_FILE - 2)
        result[(*position)++] = *text++;
    result[*position] = '\0';
}

void add_macro(Preprocessor *p, const char *line)
{
    char name[MAX_NAME] = "";
    char value[MAX_VALUE] = "";
    char parameter[MAX_NAME] = "";
    int function = 0;
    int i = 0;
    int j = 0;

    while (line[i] == ' ' || line[i] == '\t') i++;
    while (is_name_char(line[i]) && j < MAX_NAME - 1)
        name[j++] = line[i++];
    name[j] = '\0';

    if (name[0] == '\0') return;

    if (line[i] == '(')
    {
        function = 1;
        i++;
        j = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;
        while (is_name_char(line[i]) && j < MAX_NAME - 1)
            parameter[j++] = line[i++];
        parameter[j] = '\0';
        while (line[i] != '\0' && line[i] != ')') i++;
        if (line[i] == ')') i++;
    }

    while (line[i] == ' ' || line[i] == '\t') i++;
    strncpy(value, line + i, MAX_VALUE - 1);
    value[MAX_VALUE - 1] = '\0';
    value[strcspn(value, "\r\n")] = '\0';

    for (i = 0; i < p->macro_count; i++)
    {
        if (strcmp(p->macros[i].name, name) == 0) break;
    }
    if (i == p->macro_count)
    {
        if (p->macro_count >= MAX_MACROS) return;
        p->macro_count++;
    }

    strcpy(p->macros[i].name, name);
    strcpy(p->macros[i].value, value);
    strcpy(p->macros[i].parameter, parameter);
    p->macros[i].is_function = function;
}

void replace_macros(Preprocessor *p, const char *line, char *result)
{
    int i = 0;
    int position = 0;
    result[0] = '\0';

    while (line[i] != '\0' && position < MAX_FILE - 2)
    {
        if (isalpha((unsigned char)line[i]) || line[i] == '_')
        {
            char word[MAX_NAME];
            int j = 0;
            int macro_number = -1;

            while (is_name_char(line[i]) && j < MAX_NAME - 1)
                word[j++] = line[i++];
            word[j] = '\0';

            for (j = 0; j < p->macro_count; j++)
            {
                if (strcmp(word, p->macros[j].name) == 0)
                {
                    macro_number = j;
                    break;
                }
            }

            if (macro_number == -1)
            {
                add_text(result, &position, word);
            }
            else
            {
                Macro *m = &p->macros[macro_number];
                if (!m->is_function)
                {
                    add_text(result, &position, m->value);
                }
                else
                {
                    int k = i;
                    while (line[k] == ' ' || line[k] == '\t') k++;
                    if (line[k] != '(')
                    {
                        add_text(result, &position, word);
                    }
                    else
                    {
                        char argument[MAX_VALUE] = "";
                        int a = 0;
                        k++;
                        while (line[k] == ' ' || line[k] == '\t') k++;
                        while (line[k] != '\0' && line[k] != ')' && a < MAX_VALUE - 1)
                            argument[a++] = line[k++];
                        argument[a] = '\0';
                        if (line[k] == ')') k++;

                        char expanded[MAX_VALUE * 2] = "";
                        int x = 0;
                        int y = 0;
                        while (m->value[x] != '\0' && y < (int)sizeof(expanded) - 2)
                        {
                            if (strncmp(m->value + x, m->parameter, strlen(m->parameter)) == 0 &&
                                (x == 0 || !is_name_char(m->value[x - 1])) &&
                                !is_name_char(m->value[x + strlen(m->parameter)]))
                            {
                                int z = 0;
                                while (argument[z] && y < (int)sizeof(expanded) - 2)
                                    expanded[y++] = argument[z++];
                                x += (int)strlen(m->parameter);
                            }
                            else expanded[y++] = m->value[x++];
                        }
                        expanded[y] = '\0';
                        add_text(result, &position, expanded);
                        i = k;
                    }
                }
            }
        }
        else
        {
            result[position++] = line[i++];
            result[position] = '\0';
        }
    }
}
