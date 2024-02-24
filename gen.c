#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "rakivo"

#define DIR_CAP     100
#define FILE_CAP    115
#define CONTENT_CAP 125
#define CONTENTS_CAP 7

const char* const CONTENTS[CONTENTS_CAP] = {
    "fn main() {\n    println!(\"hello, world\");\n}",
    "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}",
    "#include <iostream>\n\nint main(void) {\n    std::cout << \"hello, world\" << std::endl;\n    return 0;\n}",
    "console.log(\"hello, world\");",
    "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"hello, world\")\n}",
    "print(\"hello, world\");",
};

void gen_mod_(FILE** fptr, char dir[DIR_CAP], const char* extens, const int* idx) {
    char mod_file[FILE_CAP];
    char mod_content[CONTENT_CAP];
    if (strcmp(extens, "rs")) {
        snprintf(mod_file, FILE_CAP, "%s/%s", dir, "Cargo.toml");
        snprintf(mod_content, CONTENT_CAP, 
            "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"./%s.rs\"", FILE_NAME, FILE_NAME, FILE_NAME);

        fprintf(stdout, "Creating %s.rs:\n%s\n\n", FILE_NAME, CONTENTS[*idx]);
        fprintf(stdout, "Creating Cargo.toml:\n%s\n", mod_content);
    } else if (strcmp(extens, "go")) {
        snprintf(mod_file, FILE_CAP, "%s/%s", dir, "go.mod");
        snprintf(mod_content, CONTENT_CAP, "module %s\n\ngo 1.22.0", FILE_NAME);

        fprintf(stdout, "Creating %s.go:\n%s\n\n", FILE_NAME, CONTENTS[*idx]);
        fprintf(stdout, "Creating go.mod:\n%s\n", mod_content);
    } else {
        fprintf(stdout, "ERROR: Unknown language extension: %s in directory: %s\n", extens, dir);
        exit(1);
    }
    FILE* fmod = fopen(mod_file, "w");

    fputs(CONTENTS[*idx], *fptr);
    fputs(mod_content, fmod);
    fclose(fmod);
}

void gen_(FILE** fptr, const char* extens, const int* idx) {
    if (*idx == 5 || *idx == 6) {
        fprintf(stdout, "Creating %s.%s:\n%s\n", FILE_NAME, extens, CONTENTS[5]);
        fputs(CONTENTS[5], *fptr);
        return;
    } 
    fprintf(stdout, "Creating %s.%s:\n%s\n", FILE_NAME, extens, CONTENTS[*idx]);
    fputs(CONTENTS[*idx], *fptr);
}
