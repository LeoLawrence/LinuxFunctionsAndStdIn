#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void lowercase(char* str_val) 
{
    int temp = 0;
    while (str_val[temp])
    {
        str_val[temp] = tolower(str_val[temp]);
        temp++;
    }
}

void grep(int case_sensitive, char* grep)
{
    char buf[256];
    while (fgets(buf, 1000, stdin)) // can also use !feof(stdin) and scanf("%s", buf) for these as well
    {
        if (case_sensitive)
        {
            if (strstr(buf, grep))
            {
                printf("%s", buf);
            }
        }
        else 
        {
            char temp[256];
            for (int i = 0; i < 256; i++) {
                temp[i] = buf[i];
            }
            lowercase(buf);
            lowercase(grep);
            if (strstr(buf, grep))
            {
                printf("%s", temp);
            }
        }
    }
}

int main(int argc, char* argv[]) 
{
    if (argc == 3) // check for valid flag and then it will be case insensitive
    { 
        if (strcmp(argv[1], "-i")) {
            printf("\nInvalid arguments.");
            return EXIT_FAILURE;
        }
        else {
            grep(0, argv[2]);
            return EXIT_SUCCESS;
        }
        
    }
    else if (argc == 2) { // normal grep case-sensitive program
        grep(1, argv[1]);
        return EXIT_SUCCESS;
    }
    else {
        printf("\nInvalid arguments.");
        return EXIT_FAILURE;
    }
}