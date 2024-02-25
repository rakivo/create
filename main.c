#include "gen.h"

const char* const LANGS[LANGS_LEN] = { 
    "c", "rs", "cpp", "js", "go", "py", "lua"
};

// don't sweat it CS graduates linear search in 5 elements array not that bad
static const int lang_check(const char* lang) {
    for (size_t i = 0; i < LANGS_LEN; ++i) {
        if (strcmp(LANGS[i], lang) == 0) {
            return i;
        }
    } 
    return -1;
}

// generates sample project that prints "hello, world"
static void generate(FILE** fptr, const char* file_name, char file[FILE_CAP], char dir[DIR_CAP], const int* const idx) {
    switch (*idx) {
    case 1: 
    case 4: 
        gen_mod_(fptr, file_name, dir, LANGS[*idx], idx);
        break;
    case 0:
    case 2:
    case 3:
    case 5:
    case 6:
        gen_(fptr, file_name, LANGS[*idx], idx);
        break;
    default:
        fprintf(stdout, "No case for such file: %s", file);
        break;
    } 
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: create <name> <language> <dir_name> <dir_path>\n");
        fprintf(stderr, "for instance: create test rs .\n");
        return 1;
    } 

    char lang [LANG_CAP];
    strcpy(lang, argv[2]);

    const int lang_idx = lang_check(lang);
    if (lang_idx == -1) {
        fprintf(stderr, "ERROR: invalid language: %s\nSupported languages: ", lang);
        for (size_t i = 0; i < LANGS_LEN; ++i) {
            fprintf(stderr, "%s", LANGS[i]);
            if (i < LANGS_LEN - 1) {
                fprintf(stderr, ", ");
            } 
        } fprintf(stdout, "\n");
        return 1;
    }

    char dir[DIR_CAP];
    snprintf(dir, DIR_CAP, "%s/%s/", argv[3], argv[4]);
    fprintf(stdout, "Creating directory %s..\n", dir);
    if (is_dir_exists(dir) || create_dirs(dir) != 0) {
        fprintf(stderr, "ERROR: Could not create directory or directory already exists\n");
        return 1;
    }

    char file[FILE_CAP];
    // add '/' only if it is not already present at the end
    snprintf(file, FILE_CAP, "%s%s%s.%s", dir, (dir[strlen(dir) - 1] == '/') ? "" : "/", argv[1], lang);
    fprintf(stdout, "Creating file %s..\n", file);

    FILE* fptr = fopen(file, "w");
    generate(&fptr, argv[1], file, dir, &lang_idx);

    fprintf(stdout, "All set!\n");
    fclose(fptr);
    return 0;
}
