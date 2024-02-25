#include "gen.h"

const char* const CONTENTS[CONTENTS_CAP] = {
    "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}",
    "fn main() {\n    println!(\"hello, world\");\n}",
    "#include <iostream>\n\nint main(void) {\n    std::cout << \"hello, world\" << std::endl;\n    return 0;\n}",
    "console.log(\"hello, world\");",
    "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"hello, world\")\n}",
    "print(\"hello, world\");",
};

void gen_mod_(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx) {
    char mod_file[FILE_CAP];
    char mod_content[CONTENT_CAP];
    if (strcmp(extens, "rs") == 0) {
        snprintf(mod_file, FILE_CAP, "%s/%s", dir, "Cargo.toml");
        snprintf(mod_content, CONTENT_CAP, 
            "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"./%s.rs\"", file_name, file_name, file_name);

        fprintf(stdout, "Creating %s.rs:\n%s\n\n", file_name, CONTENTS[*idx]);
        fprintf(stdout, "Creating Cargo.toml:\n%s\n", mod_content);
    } else if (strcmp(extens, "go") == 0) {
        snprintf(mod_file, FILE_CAP, "%s/%s", dir, "go.mod");
        snprintf(mod_content, CONTENT_CAP, "module %s\n\ngo 1.22.0", file_name);

        fprintf(stdout, "Creating %s.go:\n%s\n\n", file_name, CONTENTS[*idx]);
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

void gen_(FILE** fptr, const char* file_name, const char* extens, const int* const idx) {
    const int trully_index = (*idx == 5 || *idx == 6) ? 5 : *idx;
    fprintf(stdout, "Creating %s.%s:\n%s\n", file_name, extens, CONTENTS[trully_index]);
    fputs(CONTENTS[trully_index], *fptr);
}
