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

        char* tmp = strchr(new_content, '\n');
        char* tmp2 = strchr(tmp+1, '\n');

        strcat(buffer_final, "\n");
        strcat(buffer_final, tmp2+1);

        f = fopen(filename, "w");
        unsigned long last_index = strlen(buffer_final)-1;
        buffer_final[last_index] = 0;
        fputs(buffer_final, f);
        fclose(f);

        //printf("%s", buffer);

        free(buffer);
        free(buffer_final);

    } else {

        FILE* f = fopen(filename, "w");
        unsigned long last_index = strlen(new_content)-1;
        new_content[last_index] = 0;
        fputs(new_content, f);
        fclose(f);

    }

    free(new_content);
    free(filename);

    return 0;
}