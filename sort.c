#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>


int compareint(void* num1, void* num2) // done manually since harder than just using strcasecmp.
{
     int casted_num1 = * ((int*)num1);
     int casted_num2 = * ((int*)num2);

     if (casted_num1 == casted_num2){
        return 0;
     }
     else if (casted_num1 < casted_num2) {
         return -1;
     }
     else{
         return 1;
     }
}

int comparestr(void* str1, void* str2) { // takes strcasecmp and makes it usable for qsort
    return (strcasecmp(*(char **)str1, *(char **)str2));
}


int main(int argc, char* argv[]) 
{
    if (argc > 3) // too many arguments
    {
        printf("Invalid arguments.");
    }
    else if (argc > 1) // checks for flags
    {
        if (strcmp(argv[1],"-n")) {
            printf("Invalid arguments.");
            return EXIT_FAILURE;
        }
        else {
            int buf[256];
            int* inputs;
            int index = 0;
            int currSize = 1;
            inputs = calloc(1, sizeof(int));
            while (!feof(stdin)) {
                scanf("%d", buf);
                if (index >= currSize) {
                    currSize++;
                    inputs = realloc(inputs, currSize*sizeof(int));
                }
                inputs[index] = *buf;
                index++;
            }
            qsort(&inputs[0], currSize, sizeof(int), compareint);
            for (int i = 0; i < currSize-1; i++) {
                printf("%d\n", i[inputs]);
            }
            free(inputs);
        }
    }
    else // no flags
    {
        char buf[256];
        char** inputs;
        int index = 0;
        int currSize = 1;
        inputs = calloc(1, sizeof(char*));
        while (!feof(stdin)) {
            scanf("%s", buf);
            if (index >= currSize) {
                currSize++;
                inputs = realloc(inputs, currSize*sizeof(char*));
            }
            inputs[index] = malloc((strlen(buf) + 1) * sizeof(char));
            strcpy(inputs[index], buf);
            index++;
        }
        qsort(&inputs[0], index-1, sizeof(&inputs[0]), comparestr);
        for (int i = 0; i < currSize-1; i++) {
            printf("%s\n", inputs[i]);
            free(inputs[i]);
        } 
        free(inputs[currSize-1]);
        free(inputs);
    }
    return EXIT_SUCCESS;
}