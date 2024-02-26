#include "gen.h"

const char* const LANGS[LANGS_CAP] = {
    "c", "rs", "cpp", "js", "go", "php", "pas", "py", "lua"
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

#define LANG_NAME_CONFLICT(lang, file_name) fprintf(stderr, "lang: %s, and name: %s is a conflicts\n", lang, file_name);

static int check_conficts(const char* file_name, const char* lang, char dir[DIR_CAP]) {
    (void) dir;
    if (strcmp(lang, "rust") == 0 && strcmp(file_name, "test") == 0) {
        LANG_NAME_CONFLICT(lang, file_name);
        return 1;
    } else if (strcmp(lang, "go") == 0 && strcmp(file_name, "go") == 0) {
        LANG_NAME_CONFLICT(lang, file_name);
        return 1;
    }
    return 0;
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
    case 7:
    case 8:
        gen_(fptr, file_name, LANGS[*idx], idx);
        break;
    default:
        fprintf(stdout, "No case for such file: %s\n", file);
        exit(1);
        break;
    }
}

int main(int argc, char** argv) {
    if (argc < 5) {
        fprintf(stderr, "usage: create <name> <language> <dir_name> <dir_path>\n");
        fprintf(stderr, "for instance: create hello rs test .\n");
        return 1;
    }

    const int lang_idx = lang_check(argv[2]);
    if (lang_idx == -1) {
        fprintf(stderr, "ERROR: invalid language: %s\nSupported languages: ", argv[2]);
        for (size_t i = 0; i < LANGS_CAP; ++i) {
            fprintf(stderr, "%s", LANGS[i]);
            if (i < LANGS_CAP - 1) {
                fprintf(stderr, ", ");
            }
        } fprintf(stdout, "\n");
        return 1;
    }

    char dir[DIR_CAP];
    snprintf(dir, DIR_CAP, "%s/%s/", argv[3], argv[4]);
    if (check_conficts(argv[1], argv[2], argv[3]) != 0) {
        return 1;
    }
    fprintf(stdout, "Creating directory %s..\n", dir);
    if (is_dir_exists(dir) || create_dirs(dir) != 0) {
        fprintf(stderr, "ERROR: Could not create directory or directory already exists\n");
        return 1;
    }

    char file[FILE_CAP];
    // add '/' only if it is not already present at the end
    snprintf(file, FILE_CAP, "%s%s%s.%s", dir, (dir[strlen(dir) - 1] == '/') ? "" : "/", argv[1], argv[2]);
    fprintf(stdout, "Creating file %s..\n", file);

    FILE* fptr = fopen(file, "w");
    generate(&fptr, argv[1], file, dir, &lang_idx);

    fprintf(stdout, "All set!\n");
    fclose(fptr);
    return 0;
}
