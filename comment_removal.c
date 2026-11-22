#include "comment_removal.h"
#include <string.h>

/* Removes comments but keeps text inside quotes unchanged. */
void remove_comments(char *source)
{
    int i = 0;
    int j = 0;
    int state = 0; /* 0 normal, 1 line comment, 2 block comment, 3 string, 4 character */

    while (source[i] != '\0')
    {
        char ch = source[i];
        char next = source[i + 1];

        if (state == 0)
        {
            if (ch == '/' && next == '/')
            {
                state = 1;
                i += 2;
                source[j++] = ' ';
            }
            else if (ch == '/' && next == '*')
            {
                state = 2;
                i += 2;
                source[j++] = ' ';
            }
            else
            {
                source[j++] = ch;
                if (ch == '"') state = 3;
                else if (ch == '\'') state = 4;
                i++;
            }
        }
        else if (state == 1)
        {
            if (ch == '\n')
            {
                source[j++] = '\n';
                state = 0;
            }
            i++;
        }
        else if (state == 2)
        {
            if (ch == '*' && next == '/')
            {
                state = 0;
                i += 2;
            }
            else
            {
                if (ch == '\n') source[j++] = '\n';
                i++;
            }
        }
        else
        {
            source[j++] = ch;
            if (ch == '\\' && next != '\0')
            {
                source[j++] = next;
                i += 2;
            }
            else
            {
                if ((state == 3 && ch == '"') || (state == 4 && ch == '\''))
                    state = 0;
                i++;
            }
        }
    }
    source[j] = '\0';
}
