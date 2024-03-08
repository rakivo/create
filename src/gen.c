#include "gen.h"

// set mod. file, like go.mod, Cargo.toml & etc.
#define SET_MOD(file, dir, content, src) \
    if (src == 1) snprintf(file, FILE_CAP, "%s/../%s", dir, content); \
    else snprintf(file, FILE_CAP, "%s/%s", dir, content);

// set sample content to the main file
#define SET_SAMPLE(file, dir_name, sample, ...) do { \
    _Pragma("GCC diagnostic ignored \"-Wformat-extra-args\"") \
    _Pragma("GCC diagnostic ignored \"-Wunused-value\"") \
    snprintf(file, FILE_CAP, sample, dir_name, ##__VA_ARGS__); \
} while (0)

const char* const SAMPLES[SAMPLES_CAP] = {
    "#include <stdio.h>\n\nint main(void) {\n    printf(\"hello, world\\n\");\n    return 0;\n}",
    "fn main() {\n    println!(\"hello, world\");\n}",
    "#include <iostream>\n\nint main(void) {\n    std::cout << }y>}nn\"hello, world\" << std::endl;\n    return 0;\n}",
    "console.log(\"hello, world\");",
    "package main\n\nimport \"fmt\"\n\nfunc main() {\n    fmt.Println(\"hello, world\")\n}",
    "<?php\necho \"hello, world\";\n?>",
    "program hello;\nbegin\n    writeln('hello, world');\nend.",
    "fun main() {\n    println(\"hello, world\")\n}",
    "print(\"hello, world\");" // common code (for languages like python, lua, etc)
};

void gen(FILE** fptr, const char* file_name, char dir[DIR_CAP], const char* extens, const char* dir_name, const int* const idx, int src) {
    const int rs_check = strcmp(extens, "rs");
    const int go_check = strcmp(extens, "go");
    if (rs_check != 0 && go_check != 0) {
        const int common_check = *idx > 8 ? 8 : *idx;
        CREATING(file_name, extens, SAMPLES[common_check]);
        fputs(SAMPLES[common_check], *fptr);
        return;
    }

    char file[FILE_CAP];
    char content[SAMPLE_CAP];
    if (rs_check == 0) {
        SET_MOD(file, dir, "Cargo.toml", src);
        if (src == 1) {
            char toml_bin[TOML_BIN_CAP];
            snprintf(toml_bin, TOML_BIN_CAP, "src/%s", file_name);
            SET_SAMPLE(content, dir_name, TOML_MOD_SAMPLE, dir_name, toml_bin);
        }
        else SET_SAMPLE(content, dir_name, TOML_MOD_SAMPLE, file_name, file_name);
        CREATING("Cargo", "toml", content);
    } else if (go_check == 0) {
        SET_MOD(file, dir, "go.mod", src);
        SET_SAMPLE(content, file_name, GO_MOD_SAMPLE, dir_name);
        CREATING("go", "mod", content);
    } else {
        fprintf(stderr, "ERROR: Unknown language extension: %s in directory: %s\n", extens, dir);
        exit(1);
    }
    CREATING(file_name, extens, SAMPLES[*idx]);

    FILE* fmod = fopen(file, "w");

    fputs(SAMPLES[*idx], *fptr);
    fputs(content, fmod);
    fclose(fmod);
}
