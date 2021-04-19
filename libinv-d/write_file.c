//
// Created by user0 on 4/17/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "write_file.h"

int write_file(char* new_content, char* filename)
{
    if(access(filename, F_OK) == 0) {
        unsigned long ll = 0;
        unsigned long size;
        char* buffer;
        char* buffer_final;

        FILE* f = fopen(filename, "r+");
        fseek(f, 0,SEEK_END);
        size = ftell(f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc(sizeof(char) * size);
        fread(buffer, 1, size, f);
        fclose(f);

        //printf("Size: %lu", size);

        for (unsigned long i = size-1; ll == 0 ; --i) {
            if (buffer[i] == '\n') {
                ll = i;
            }
        }

        buffer[ll] = '\0';
        buffer_final = malloc(sizeof(char) * (size+strlen(new_content)));
        strcpy(buffer_final, buffer);

        // TODO: remove the first two lines
        strcat(buffer_final, new_content);

        f = fopen(filename, "w");
        fputs(buffer_final, f);
        fclose(f);

        //printf("%s", buffer);

        free(buffer);
        //free(buffer_final);

    } else {

        FILE* f = fopen(filename, "w");
        fputs(new_content, f);
        fclose(f);

    }

    free(new_content);
    free(filename);

    return 0;
}