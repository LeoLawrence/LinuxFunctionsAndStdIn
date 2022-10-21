#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <strings.h>

int alphasort_CI(const struct dirent** dir1, const struct dirent** dir2) {
    return strcasecmp((*dir1)->d_name, (*dir2)->d_name);
}

int main(int argc, char* argv[])
{
    if (argc > 3) { // too many arguments
        printf("Invalid arguments.");
        return EXIT_FAILURE;
    }
    else if (argc == 2) {
        if (strcmp(argv[1], "-l")) { // argument has to be -l
            printf("Invalid arguments.");
            return EXIT_FAILURE;
        }
        else {
            // DIR* currDir;
            // struct dirent* dir;
            // currDir = opendir("."); // . is current directory

            struct dirent** dirList;
            int currDir;
            currDir = scandir(".", &dirList, 0, alphasort_CI);
            if (currDir >= 0) {
                for (int i = 0; i < currDir; i++) {
                if (dirList[i]->d_name[0] != '.') {
                    if (dirList[i]->d_type == DT_DIR) {
                        printf("d");
                    }
                    else {
                        printf("-");
                    }
                    struct stat st;
                    stat(dirList[i]->d_name, &st);
                    // extract user bits
                    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
                    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
                    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
                    // extract group bits
                    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
                    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
                    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
                    // extract other bits
                    printf( (st.st_mode & S_IROTH) ? "r" : "-");
                    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
                    printf( (st.st_mode & S_IXOTH) ? "x " : "- ");
                    struct passwd* p;
                    if (!(p = getpwuid(st.st_uid))) {
                        printf("%d ", st.st_uid);
                    }
                    else {
                        printf("%s ", p->pw_name);
                    }
                    struct group* gp;
                    if (!(gp = getgrgid(st.st_gid))) {
                        printf("%d ", st.st_gid);
                    }
                    else {
                        printf("%s ", ((getgrgid(st.st_gid)))->gr_name);
                    }
                    printf("%ld ", st.st_size);
                    time_t stat_time;
                    stat_time = st.st_ctime;
                    char buf[63];
                    struct tm* format_time;
                    format_time = localtime(&stat_time);
                    strftime(buf, sizeof(buf), " %b %d %H:%M", format_time);
                    printf("%s ", buf);
                    printf("%s\n", dirList[i]->d_name);
                }
                free(dirList[i]);
                }
                free(dirList);
            }
            return EXIT_SUCCESS;
        }
    }
    else {
        //DIR* currDir;
        //struct dirent* dir;
        struct dirent** dirList;
        int currDir;
        currDir = scandir(".", &dirList, 0, alphasort_CI);
        if (currDir >= 0) {
            for (int i = 0; i < currDir; i++) {
                if (dirList[i]->d_name[0] != '.') {
                    printf("%s\n", dirList[i]->d_name);
                }
                free(dirList[i]);
            }
            free(dirList);
        }
        return EXIT_SUCCESS;
    }
    
}