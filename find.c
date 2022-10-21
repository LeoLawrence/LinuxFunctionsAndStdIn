#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

void recurse(char* curr, char* target) {
    char path[1024];
    DIR* currDir = opendir(curr);
    struct dirent *dir;

    while ((dir = readdir(currDir))) {
        if (dir->d_name[0] != '.') { // ignore hidden files

            strcpy(path, curr);
            strcat(path, "/");
            strcat(path, dir->d_name);

            if (strstr(dir->d_name, target)) {
                printf("%s\n", path);
            }

            if (dir->d_type == DT_DIR) { // only opens directories
                recurse(path, target);
            }
        }
    }

    closedir(currDir);
}

int main(int argc, char* argv[])
{
    if (argc > 3) { 
        printf("Invalid arguments.");
        return EXIT_FAILURE;
    }
    else {
        recurse(".", argv[1]); // starts at curr directory
        return EXIT_SUCCESS;
    }
    
}