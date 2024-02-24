#include <stdio.h> 
#include <string.h>
#include <sys/stat.h>

#include <errno.h>  
#include <unistd.h>

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
        fprintf(stdout, "Generate C++ project is not implemented yet");
        break;
    default:
        break;
    } 
}

int create_directory(const char* dir_path) {
    if (mkdir(dir_path, 0777) == -1 && errno != EEXIST) {
        perror("ERROR");
        fprintf(stderr, "ERROR: Could not create directory %s\n", dir_path);
        return 1;
    }
    return 0;
}

int create_directories(const char* dir_path) {
    char tmp[DIR_CAP];
    char* p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", dir_path);
    len = strlen(tmp);
    if (tmp[len - 1] == '/')
        tmp[len - 1] = 0;

    for (p = tmp + 1; *p; p++)
        if (*p == '/') {
            *p = 0;
            create_directory(tmp);
            *p = '/';
        }
    create_directory(tmp);

    return 0;
}

int main(int argc, char** argv) {
    if (argc < 4) {
        fprintf(stderr, "usage: create <dir_name> <language> <dir_path>\n");
        fprintf(stderr, "for instance: create test c .\n");
        return 1;
    } 

    char lang[LANG_CAP];
    strcpy(lang, argv[2]);

    const int lang_idx = check(lang);
    if (lang_idx == -1 && errno != EEXIST) {
        perror("ERROR");
        fprintf(stderr, "ERROR: invalid language: %s\n", lang);
        return 1;
    }

    char dir[DIR_CAP];
    snprintf(dir, DIR_CAP, "%s/%s/", argv[3], argv[1]);
    fprintf(stdout, "Creating directory %s..\n", dir);
    if (create_directories(dir) != 0) {
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
