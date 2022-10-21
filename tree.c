#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int alphasort_CI(const struct dirent** dir1, const struct dirent** dir2) {
    return strcasecmp((*dir1)->d_name, (*dir2)->d_name);
}

void recurse(char* curr, int tab) {
    char path[1024];
    struct dirent** dirList;
    int currDir;
    currDir = scandir(curr, &dirList, 0, alphasort_CI);

    for (int i = 0; i < currDir; i++) {
        if (dirList[i]->d_name[0] != '.') { // ignore hidden files
            for (int i = 0; i < tab; i++) {
                if (i >= 0) {
                    printf("\t");
                }
            }

            printf("%s\n", dirList[i]->d_name);

            if (dirList[i]->d_type == DT_DIR) { // only opens directories
                strcpy(path, curr);
                strcat(path, "/");
                strcat(path, dirList[i]->d_name);

                recurse(path, tab + 1);
            }
        }
        free(dirList[i]);
    }
    free(dirList);
}

int main(int argc, char* argv[])
{
    if (argc > 1) { 
        char* removeFlag = argv[0];
        if (removeFlag) {
            printf("Invalid arguments.");
            return EXIT_FAILURE;
        }
        else {
            printf("Invalid arguments.");
            return EXIT_FAILURE;
        }
    }
    else {
        recurse(".", 0); // starts at curr directory
        return EXIT_SUCCESS;
    }
    
}