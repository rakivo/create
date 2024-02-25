#ifndef GEN
#define GEN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIR_CAP      100
#define FILE_CAP     115
#define CONTENT_CAP  125
#define CONTENTS_CAP 7
#define LANGS_CAP    7

extern const char* const LANGS[LANGS_CAP];

int is_dir_exists(const char* dir_path);
int create_dir_(const char* dir_path);
int create_dirs(const char* dir_path);

void gen_(FILE** fptr, const char* file_name, const char* extens, const int* const idx);
void gen_mod_(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx);

#endif // GEN
