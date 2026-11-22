#ifndef MACRO_HANDLER_H
#define MACRO_HANDLER_H
#include "preprocessor.h"

void add_macro(Preprocessor *p, const char *line);
void replace_macros(Preprocessor *p, const char *line, char *result);

#endif
