#include <stdio.h>

#define FILE_NAME "rakivo"

#define DIR_CAP     100
#define FILE_CAP    115
#define CONTENT_CAP 125

void rsgen_(FILE** fptr, char dir[DIR_CAP]) {
    char* content = "fn main() {\n    println!(\"hello, world\");\n}";

    char toml_file[FILE_CAP];
    char toml_content[CONTENT_CAP];
    snprintf(toml_file, FILE_CAP, "%s/%s", dir, "Cargo.toml");
    snprintf(toml_content, CONTENT_CAP, "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"./%s.rs\"", FILE_NAME, FILE_NAME, FILE_NAME);

    fprintf(stdout, "Creating %s.rs:\n%s\n\n", FILE_NAME, content);
    fprintf(stdout, "Creating Cargo.toml:\n%s\n", toml_content);
    FILE* ftoml = fopen(toml_file, "w");

    fputs(content, *fptr);
    fputs(toml_content, ftoml);

    fclose(ftoml);
}

void cgen_(FILE** fptr) {
    char* content = "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}";
    fprintf(stdout, "Creating %s.c:\n%s\n", FILE_NAME, content);
    fputs(content, *fptr);
}

void cppgen_(FILE** fptr) {
    char* content = "#include <iostream>\n\nint main(void) {\n    std::cout << \"hello, world\" << std::endl;\n    return 0;\n}";
    fprintf(stdout, "Creating %s.cpp:\n%s\n", FILE_NAME, content);
    fputs(content, *fptr);
}

void jsgen_(FILE** fptr) {
    char* content = "console.log(\"hello, world\");";
    fprintf(stdout, "Creating %s.js:\n%s\n", FILE_NAME, content);
    fputs(content, *fptr);
}

void gogen_(FILE** fptr, char dir[DIR_CAP]) {
    char* content = "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"hello, world\")\n}";

    char gomod_file[FILE_CAP];
    char gomod_content[CONTENT_CAP];
    snprintf(gomod_file, FILE_CAP, "%s/%s", dir, "go.mod");
    snprintf(gomod_content, CONTENT_CAP, "module %s\n\ngo 1.22.0", FILE_NAME);

    fprintf(stdout, "Creating %s.go:\n%s\n\n", FILE_NAME, content);
    fprintf(stdout, "Creating go.mod:\n%s\n", gomod_content);
    FILE* fgomod = fopen(gomod_file, "w");

    fputs(content, *fptr);
    fputs(gomod_content, fgomod);

    fclose(fgomod);
}

void gen_(FILE** fptr, const int* lang) {
    char* content = "print(\"hello, world\");";
    char* extens  = *lang == 5 ? "py" : "lua";
    fprintf(stdout, "Creating %s.%s:\n%s\n", FILE_NAME, extens, content);
    fputs(content, *fptr);
}
