#include <errno.h>

#include "gen.h"

int create_dir_(char* dir_path) { // create a single directory
    if (mkdir(dir_path, 0777) == -1 && errno != EEXIST) {
        perror("ERROR");
        exit(1);
    }
    return 0;
}

int create_dirs(char* dir_path, int src) { // create nested directories
    char curr_dir[DIR_CAP]; snprintf(curr_dir, DIR_CAP, "%s", dir_path);

    size_t n = strlen(curr_dir);
    if (curr_dir[n - 1] == '/') curr_dir[n - 1] = 0;
    for (char* p = curr_dir + 1; *p; ++p) {
        if (*p == '/') {
            *p = 0;
            create_dir_(curr_dir);
            *p = '/';
        }
    }
    create_dir_(curr_dir);
    if (src) create_dir_(strcat(dir_path, "src"));
    return 0;
}
