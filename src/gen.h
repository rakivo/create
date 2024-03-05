#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define TOML_BIN_CAP 64
#define DIR_CAP      128
#define FILE_CAP     256
#define SAMPLE_CAP   512

#define SAMPLES_CAP 9
#define LANGS_CAP   10

extern const char* const LANGS[LANGS_CAP];

int create_dir_(char* dir_path);
int create_dirs(char* dir_path, int src);

void gen(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx, int src);
