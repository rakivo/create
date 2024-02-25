#include <stdarg.h>

#include "gen.h"

const char* const CONTENTS[CONTENTS_CAP] = {
    "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}",
    "fn main() {\n    println!(\"hello, world\");\n}",
    "#include <iostream>\n\nint main(void) {\n    std::cout << \"hello, world\" << std::endl;\n    return 0;\n}",
    "console.log(\"hello, world\");",
    "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"hello, world\")\n}",
    "print(\"hello, world\");",
};

#define TOML_MOD_CONTENT "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"./%s.rs\""
#define GO_MOD_CONTENT   "module %s\n\ngo 1.22.0"

#define SET_MOD(file, dir, content) snprintf(file, FILE_CAP, "%s/%s", dir, content)
#define SET_MOD_CONTENT(mod_file, file_name, sample, ...) do { \
        _Pragma("GCC diagnostic ignored \"-Wformat-extra-args\"") \
        _Pragma("GCC diagnostic ignored \"-Wunused-value\"") \
        snprintf(mod_file, FILE_CAP, sample, file_name, ##__VA_ARGS__); \
    } while (0)
#define CREATING(file_name, extens, content) fprintf(stdout, "Creating %s.%s:\n%s\n\n", file_name, extens, content);

void gen_mod_(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx) {
    char mod_file[FILE_CAP];
    char mod_content[CONTENT_CAP];
    if (strcmp(extens, "rs") == 0) {
        SET_MOD(mod_file, dir, "Cargo.toml");
        SET_MOD_CONTENT(mod_content, file_name, TOML_MOD_CONTENT, file_name, file_name, file_name);
        CREATING("Cargo", "toml", mod_content);
    } else if (strcmp(extens, "go") == 0) {
        SET_MOD(mod_file, dir, "go.mod");
        SET_MOD_CONTENT(mod_content, file_name, GO_MOD_CONTENT, file_name);
        CREATING("go", "mod", mod_content);
    } else {
        fprintf(stdout, "ERROR: Unknown language extension: %s in directory: %s\n", extens, dir);
        exit(1);
    }
    CREATING(file_name, extens, CONTENTS[*idx]);
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
