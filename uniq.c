#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

// finds adjacent duplicates 

int main(int argc, char* argv[]) 
{
    if (argc > 1) {
        printf("Invalid arguments");
        return EXIT_FAILURE;
    }
    else {
        char buf[256];
        char** inputs;
        int index = 0;
        int currSize = 1;
        inputs = calloc(1, sizeof(char*));
        while (!feof(stdin)) { // gathers all the strings and puts them in an array
            scanf("%s", buf);
            if (index >= currSize) {
                currSize++;
                inputs = realloc(inputs, currSize*sizeof(char*));
            }
            inputs[index] = malloc((strlen(buf) + 1) * sizeof(char));
            strcpy(inputs[index], buf);
            index++;
        }
        //printf("Current size: %d\n", currSize);
        // above code reads the words perfectly. counting duplicates logic is incomplete.

        if (index == 0) {
            free(inputs);
            return EXIT_SUCCESS;
        }
        else if (index < 2) {
            printf("1 %s", inputs[0]);
        }
        else {
            int counter = 0;
            int wordCount = 1;
            while (counter < currSize-1) { // currSize is 1 more than the # of strings, so currSize-1 is the actual size.
                if (counter < currSize-2) {
                    if (!strcmp(inputs[counter], inputs[counter+1])) {
                        wordCount++;
                    }
                    else {
                        printf("%d %s\n", wordCount, inputs[counter]);
                        wordCount = 1;
                    }
                }
                else {
                    printf("%d %s\n", wordCount, inputs[counter]);
                }
                counter++;
            }
        }
        for (int i = 0; i < index; i++) {
            free(inputs[i]);
        }
        free(inputs);
        return EXIT_SUCCESS;
    }
}