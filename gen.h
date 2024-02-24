#ifndef GEN
#define GEN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "rakivo"

#define DIR_CAP     100
#define FILE_CAP    115
#define CONTENT_CAP 125
#define CONTENTS_CAP 7
#define LANG_CAP 4

#define LANGS_N  7
extern const char* const LANGS[LANGS_N];

int lang_check(const char* lang);
int is_dir_exists(const char* dir_path);
int create_dir_(const char* dir_path);
int create_dirs(const char* dir_path);

void gen_(FILE** fptr, const char* extens, const int* idx);
void gen_mod_(FILE** fptr, char dir[DIR_CAP], const char* extens, const int* idx);
void generate(FILE** fptr, char file[FILE_CAP], char dir[DIR_CAP], const int* idx);

#endif // GEN
