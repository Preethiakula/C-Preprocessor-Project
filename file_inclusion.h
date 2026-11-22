#ifndef FILE_INCLUSION_H
#define FILE_INCLUSION_H

int get_include_name(const char *line, char *file_name);
void make_include_path(const char *current_file, const char *include_name, char *full_path);

#endif
