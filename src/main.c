#include "gen.h"

#define CREATE_DIRS(dir, info, src) do { \
    if ((stat(dir, &info) == 0 && S_ISDIR(info.st_mode)) || create_dirs(dir, src) != 0) { \
        fprintf(stderr, "ERROR: Could not create directory or directory already exists\n"); \
        return 1; \
    } \
} while (0)

#define CHECK_CONFLICTS(ret, file_name, lang) do { \
    if (strcmp(lang, "rs") == 0 && strcmp(file_name, "test") == 0) { \
        LANG_NAME_CONFLICT(lang, file_name); \
        ret = 1; \
    } else if (strcmp(lang, "go") == 0 && strcmp(file_name, "go") == 0) { \
        LANG_NAME_CONFLICT(lang, file_name); \
        ret = 1; \
    } \
} while (0)

// don't sweat it CS graduates linear search in 5 elements array not that bad
#define LANG_CHECK(ret, lang) { \
    for (size_t i = 0; i < LANGS_CAP; ++i) { \
        if (strcmp(LANGS[i], lang) == 0) { \
            ret = i; \
        } \
    } \
}

const char* const LANGS[LANGS_CAP] = {
    "c", "rs", "cpp", "js", "go", "php", "pas", "kt", "py", "lua"
};

int main(int argc, char** argv) {
    if (argc >= 1 && argc < 5) {
        if (argc == 1) fprintf(stderr, "usage: create h, or: create help TO show supported languages and commands.\n");
        else if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0) {
            USAGE;
            SHOW_SUPPORTED_LANGS(stdout);
        } else USAGE;
        return 1;
    }

    int lang_idx = -1; LANG_CHECK(lang_idx, argv[2]);
    if (lang_idx == -1) {
        fprintf(stderr, "ERROR: invalid language: %s\nSupported languages: ", argv[2]);
        SHOW_SUPPORTED_LANGS(stderr);
        return 1;
    }

    char dir[DIR_CAP];
    snprintf(dir, DIR_CAP, "%s/%s/", argv[3], argv[4]);

    int is_conflict = 0; CHECK_CONFLICTS(is_conflict, argv[2], argv[3]);
    if (is_conflict != 0) return 1;
    fprintf(stdout, "Creating directory %s..\n", dir);

    int src = 0;
    struct stat info;
    if (lang_idx == 1) { // asking only for Rust
        fprintf(stdout, "Create src directory for a %s.%s file? [y/n] ", argv[1], argv[2]);
        char check; int ans;
        GET_USER_INPUT(check, ans);
        if (ans == 1) {
            src = 1;
            CREATE_DIRS(dir, info, 1);
        } else CREATE_DIRS(dir, info, 0);
    } else CREATE_DIRS(dir, info, 0);

    char file[FILE_CAP];
    // add '/' only if it is not already present at the end
    snprintf(file, FILE_CAP, "%s%s%s.%s", dir, (dir[strlen(dir) - 1] == '/') ? "" : "/", argv[1], argv[2]);
    fprintf(stdout, "Creating file %s..\n", file);

    FILE* fptr = fopen(file, "w");
    if (fptr == NULL) {
        perror("ERROR opening file");
        return 1;
    }

    gen(&fptr, argv[1], dir, argv[2], argv[3], &lang_idx, src);

    ALL_SET;
    fclose(fptr);
    return 0;
}
