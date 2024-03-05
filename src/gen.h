#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// <================================================- CAPACITIES - ===============================================>

#define TOML_BIN_CAP 64
#define DIR_CAP      128
#define FILE_CAP     256
#define SAMPLE_CAP   512

#define SAMPLES_CAP 9
#define LANGS_CAP   10

// <============================================== - DECLARATIONS - ==============================================>

extern const char* const LANGS[LANGS_CAP];

int create_dir_(char* dir_path);
int create_dirs(char* dir_path, int src);

void gen(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx, int src);

// <================================================= - SAMPLES - =================================================>

#define TOML_MOD_SAMPLE "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"%s.rs\""
#define GO_MOD_SAMPLE   "module %s\n\ngo 1.22.0"

// <================================================= - LOGGING - =================================================>

#define CREATING(file_name, extens, content) \
    fprintf(stdout, "<========================>\n"); \
    fprintf(stdout, "Creating %s.%s:\n%s\n", file_name, extens, content); \

#define USAGE do { \
    fprintf(stdout, "usage: create <name> <language> <dir_name> <dir_path>\n"); \
    fprintf(stdout, "for instance: create hello rs test .\n"); \
} while (0)

#define SHOW_SUPPORTED_LANGS(out) do { \
    for (size_t i = 0; i < LANGS_CAP; ++i) { \
        fprintf(out, "%s", LANGS[i]); \
        if (i < LANGS_CAP - 1) { \
            fprintf(out, ", "); \
        } \
    } fprintf(out, "\n"); \
} while (0)

#define LANG_NAME_CONFLICT(lang, file_name) fprintf(stderr, "ERROR: lang: %s, and name: %s is a conflict\n", lang, file_name);

#define GET_USER_INPUT(buf, ret) do { \
    do { \
        buf = getchar(); \
        if ('A' <= buf && buf <= 'Z') buf = ('a' + (buf - 'A')); \
        if (buf != 'y' && buf != 'n') { \
            fprintf(stdout, "enter y or n "); \
            while (getchar() != '\n'); \
        } \
    } while (buf != 'y' && buf != 'n'); \
    if (buf == 'y') ret = 1; else ret = 0; \
} while (0)

#define ALL_SET do { \
    fprintf(stdout, "<======>\n"); \
    fprintf(stdout, "All set!\n"); \
    fprintf(stdout, "<======>\n"); \
} while (0)
