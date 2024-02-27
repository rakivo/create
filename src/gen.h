#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define DIR_CAP     128
#define FILE_CAP    256
#define SAMPLE_CAP  256

#define SAMPLES_CAP 9
#define LANGS_CAP   10

extern const char* const LANGS[LANGS_CAP];

int create_dir_(const char* dir_path);
int create_dirs(const char* dir_path);

void gen(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx);
