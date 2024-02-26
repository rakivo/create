#include "gen.h"

#define TOML_MOD_SAMPLE "[package]\nname = \"%s\"\nversion = \"0.1.0\"\nedition = \"2021\"\n\n[dependencies]\n\n[[bin]]\nname = \"%s\"\npath = \"./%s.rs\""
#define GO_MOD_SAMPLE   "module %s\n\ngo 1.22.0"

#define SET_MOD(file, dir, content) snprintf(file, FILE_CAP, "%s/%s", dir, content)
#define SET_SAMPLE(file, file_name, sample, ...) do { \
        _Pragma("GCC diagnostic ignored \"-Wformat-extra-args\"") \
        _Pragma("GCC diagnostic ignored \"-Wunused-value\"") \
        snprintf(file, FILE_CAP, sample, file_name, ##__VA_ARGS__); \
    } while (0)
#define CREATING(file_name, extens, content) fprintf(stdout, "Creating %s.%s:\n%s\n\n", file_name, extens, content);

const char* const SAMPLES[SAMPLES_CAP] = {
    "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}",
    "fn main() {\n    println!(\"hello, world\");\n}",
    "#include <iostream>\n\nint main(void) {\n    std::cout << }y>}nn\"hello, world\" << std::endl;\n    return 0;\n}",
    "console.log(\"hello, world\");",
    "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"hello, world\")\n}",
    "<?php\necho \"hello, world\";\n?>",
    "program hello;\nbegin\n    writeln('hello, world');\nend.",
    "fun main() {\n    println(\"hello, world\")\n}",
    "print(\"hello, world\");"
};

void gen_mod_(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const int* const idx) {
    char file[FILE_CAP];
    char content[SAMPLE_CAP];
    if (strcmp(extens, "rs") == 0) {
        SET_MOD(file, dir, "Cargo.toml");
        SET_SAMPLE(content, file_name, TOML_MOD_SAMPLE, file_name, file_name, file_name);
        CREATING("Cargo", "toml", content);
    } else if (strcmp(extens, "go") == 0) {
        SET_MOD(file, dir, "go.mod");
        SET_SAMPLE(content, file_name, GO_MOD_SAMPLE, file_name);
        CREATING("go", "mod", content);
    } else {
        fprintf(stdout, "ERROR: Unknown language extension: %s in directory: %s\n", extens, dir);
        exit(1);
    }
    CREATING(file_name, extens, SAMPLES[*idx]);
    FILE* fmod = fopen(file, "w");

    fputs(SAMPLES[*idx], *fptr);
    fputs(content, fmod);
    fclose(fmod);
}

void gen_(FILE** fptr, const char* file_name, const char* extens, const int* const idx) {
    const int trully_index = *idx > 6 ? 7 : *idx;
    CREATING(file_name, extens, SAMPLES[trully_index]);
    fputs(SAMPLES[trully_index], *fptr);
}
