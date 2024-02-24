#include <stdio.h> 
#include <string.h>

#define FILE_NAME "test"

#define LANGS_N 3
char* LANGS[] =  { "c", "rs", "cpp" };

// linear check not so bad in this case don't sweat it
int check(const char* lang) {
    for (size_t i = 0; i < LANGS_N; ++i) {
        if (strcmp(LANGS[i], lang) == 0) {
            return i;
        }
    } 
    return -1;
}

void generate(FILE** fptr, const int* idx) {
    switch (*idx) {
    case 0:
        fprintf(*fptr, 
                "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}");
        break;
    case 1: 
        fprintf(*fptr, 
                "fn main() {\n    println!(\"hello, world\");\n}");
        break;
    default:
        break;
    } 
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: create <language>\n");
        fprintf(stderr, "for instance: create c\n");
        return 1;
    } 

    char lang[2];
    strcpy(lang, argv[1]);
    const int lang_idx = check(lang);
    if (lang_idx == -1) {
        fprintf(stderr, "ERROR: invalid language: %s\n", lang);
        return 1;
    }

    char file[10];
    snprintf(file, sizeof(file), "%s.%s", FILE_NAME, lang);
    FILE* fptr = fopen(file, "w");
    generate(&fptr, &lang_idx);

    fclose(fptr);
    return 0;
}
