#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include "gen.h"

const char* const LANGS[LANGS_N] = { 
    "c", "rs", "cpp", "js", "go", "py", "lua"
};

// don't sweat it CS graduates linear search in 5 elements array not that bad
int lang_check(const char* lang) {
    for (size_t i = 0; i < LANGS_N; ++i) {
        if (strcmp(LANGS[i], lang) == 0) {
            return i;
        }
    } 
    return -1;
}

int is_dir_exists(const char* dir_path) {
    struct stat info;
    return stat(dir_path, &info) == 0 && S_ISDIR(info.st_mode);
}

int create_dir_(const char* dir_path) {
    if (mkdir(dir_path, 0777) == -1 && errno != EEXIST) {
        perror("ERROR");
        return 1;
    }
    return 0;
}

int create_dirs(const char* dir_path) {
    char curr_dir[DIR_CAP];
    snprintf(curr_dir, DIR_CAP, "%s", dir_path);
    
    size_t n = strlen(curr_dir);
    if (curr_dir[n - 1] == '/') {
        curr_dir[n - 1] = 0;
    }
    for (char* p = curr_dir + 1; *p; p++) {
        if (*p == '/') {
            *p = 0;
            create_dir_(curr_dir);
            *p = '/';
        }
    }
    create_dir_(curr_dir);

    return 0;
}

// generates sample project that prints "hello, world"
void generate(FILE** fptr, char file[FILE_CAP], char dir[DIR_CAP], const int* idx) {
    switch (*idx) {
    case 1: 
    case 4: 
        gen_mod_(fptr, dir, LANGS[*idx], idx);
        break;
    case 0:
    case 2:
    case 3:
    case 5:
    case 6:
        gen_(fptr, LANGS[*idx], idx);
        break;
    default:
        fprintf(stdout, "No case for such file: %s", file);
        break;
    } 
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: create <dir_name> <language> <dir_path>\n");
        fprintf(stderr, "for instance: create test rs .\n");
        return 1;
    } 

    char lang[LANG_CAP];
    strcpy(lang, argv[2]);

    const int lang_idx = lang_check(lang);
    if (lang_idx == -1) {
        fprintf(stderr, "ERROR: invalid language: %s\nSupported languages: ", lang);
        // pretty print
        for (size_t i = 0; i < LANGS_N; ++i) {
            fprintf(stderr, "%s", LANGS[i]);
            if (i < LANGS_N - 1) {
                fprintf(stderr, ", ");
            } 
        } fprintf(stdout, "\n");
        return 1;
    }

    char dir[DIR_CAP];
    snprintf(dir, DIR_CAP, "%s/%s/", argv[3], argv[1]);
    fprintf(stdout, "Creating directory %s..\n", dir);
    if (is_dir_exists(dir) || create_dirs(dir) != 0) {
        fprintf(stderr, "ERROR: Could not create directory or directory already exists\n");
        return 1;
    }

    char file[FILE_CAP];
    // add '/' only if it is not already present at the end
    snprintf(file, FILE_CAP, "%s%s%s.%s", dir, (dir[strlen(dir) - 1] == '/') ? "" : "/", FILE_NAME, lang);
    fprintf(stdout, "Creating file %s..\n", file);

    FILE* fptr = fopen(file, "w");
    generate(&fptr, file, dir, &lang_idx);

    fprintf(stdout, "All set!\n");
    fclose(fptr);
    return 0;
}
