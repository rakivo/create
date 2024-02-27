#include "gen.h"

#define USAGE \
    fprintf(stdout, "usage: create <name> <language> <dir_name> <dir_path>\n"); \
    fprintf(stdout, "for instance: create hello rs test .\n");

#define SHOW_SUPPORTED_LANGS(out) \
    fprintf(stdout, "Supported languages: "); \
    for (size_t i = 0; i < LANGS_CAP; ++i) { \
        fprintf(out, "%s", LANGS[i]); \
        if (i < LANGS_CAP - 1) { \
            fprintf(out, ", "); \
        } \
    } fprintf(out, "\n");

#define LANG_NAME_CONFLICT(lang, file_name) fprintf(stderr, "ERROR: lang: %s, and name: %s is a conflict\n", lang, file_name);

#define ALL_SET \
    fprintf(stdout, "<======>\n"); \
    fprintf(stdout, "All set!\n"); \
    fprintf(stdout, "<======>\n");

const char* const LANGS[LANGS_CAP] = {
//   0     1     2      3     4     5      6      7     8     9
    "c", "rs", "cpp", "js", "go", "php", "pas", "kt", "py", "lua"
};

// don't sweat it CS graduates linear search in 5 elements array not that bad
static int lang_check(const char* lang) {
    for (size_t i = 0; i < LANGS_CAP; ++i) {
        if (strcmp(LANGS[i], lang) == 0) {
            return i;
        }
    }
    return -1;
}

static int check_conficts(const char* file_name, const char* lang, char dir[DIR_CAP]) {
    (void) dir; // i let dir last maybe for future. ((void) it for have no warnings)
    if (strcmp(lang, "rs") == 0 && strcmp(file_name, "test") == 0) {
        LANG_NAME_CONFLICT(lang, file_name);
        return 1;
    } else if (strcmp(lang, "go") == 0 && strcmp(file_name, "go") == 0) {
        LANG_NAME_CONFLICT(lang, file_name);
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc > 0 && argc < 5) {
        if (argc == 1) { fprintf(stderr, "usage: create h, or: create help TO show supported languages and commands.\n"); } 
        else if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) { USAGE SHOW_SUPPORTED_LANGS(stdout) } 
        else { USAGE }
        return 1;
    }

    const int lang_idx = lang_check(argv[2]);
    if (lang_idx == -1) {
        fprintf(stderr, "ERROR: invalid language: %s\nSupported languages: ", argv[2]);
        SHOW_SUPPORTED_LANGS(stderr)
        return 1;
    }

    char dir[DIR_CAP];
    snprintf(dir, DIR_CAP, "%s/%s/", argv[3], argv[4]);
    if (check_conficts(argv[1], argv[2], argv[3]) != 0) return 1;
    fprintf(stdout, "Creating directory %s..\n", dir);

    struct stat info;
    if ((stat(dir, &info) == 0 && S_ISDIR(info.st_mode)) || create_dirs(dir) != 0) {
        fprintf(stderr, "ERROR: Could not create directory or directory already exists\n");
        return 1;
    }
    char file[FILE_CAP];
    // add '/' only if it is not already present at the end
    snprintf(file, FILE_CAP, "%s%s%s.%s", dir, (dir[strlen(dir) - 1] == '/') ? "" : "/", argv[1], argv[2]);
    fprintf(stdout, "Creating file %s..\n", file);

    FILE* fptr = fopen(file, "w");

    gen(&fptr, argv[1], dir, argv[2], &lang_idx);

    ALL_SET
    fclose(fptr);
    return 0;
}
