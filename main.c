#include <stdio.h> 
#include <string.h>
#include <sys/stat.h>

#define FILE_NAME "rakivo"

#define FILE_CAP       110
#define DIR_CAP        100

#define CONTENT_CAP    256

#define LANG_CAP 3
#define LANGS_N  3
const char* const LANGS[] =  { "c", "rs", "cpp" };

// linear check not so bad in this case don't sweat it
int check(const char* lang) {
    for (size_t i = 0; i < LANGS_N; ++i) {
        if (strcmp(LANGS[i], lang) == 0) {
            return i;
        }
    } 
    return -1;
}

int is_dir_exists(const char* path) {
    struct stat info;
    return stat(path, &info) == 0 && S_ISDIR(info.st_mode);
}

int create_dir_(const char* dir_path) {
    if (mkdir(dir_path, 0777) == -1) {
        perror("ERROR");
        return 1;
    }
    return 0;
}

int create_dirs(const char* dir_path) {
    char curr_dir[DIR_CAP];
    snprintf(curr_dir, sizeof(curr_dir), "%s", dir_path);
    
    size_t len = strlen(curr_dir);
    if (curr_dir[len - 1] == '/') {
        curr_dir[len - 1] = 0;
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

void generate(FILE** fptr, char file[FILE_CAP], char dir[DIR_CAP], const int* idx) {
    switch (*idx) {
    case 0:
        fprintf(*fptr, 
                "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}");
        break;
    case 1: 
        fprintf(*fptr, 
                "fn main() {\n    println!(\"hello, world\");\n}");

        char toml_file[FILE_CAP];
        char content[CONTENT_CAP];
        snprintf(toml_file, FILE_CAP, "%s/%s", dir, "Cargo.toml");
        snprintf(content, CONTENT_CAP, "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"./%s.rs\"",
                 FILE_NAME, FILE_NAME, FILE_NAME);
        fprintf(stdout, "Creating Cargo.toml:\n%s..\n", content);

        FILE* ftoml = fopen(toml_file, "w");
        fputs(content, ftoml);

        fclose(ftoml);
        break;
    case 3:
        fprintf(stdout, "Generating C++ project is not implemented yet");
        break;
    default:
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

    const int lang_idx = check(lang);
    if (lang_idx == -1) {
        perror("ERROR");
        fprintf(stderr, "ERROR: invalid language: %s\n", lang);
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
