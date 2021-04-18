//
// Created by user0 on 4/17/21.
//

#include <stdio.h>
#include <unistd.h>
#include "write_file.h"

int write_file(char* new_content, char* filename)
{
    if(access(filename, F_OK) == 0) {

        printf("HOURRA\n");
        // TODO Manage xml merge

    } else {

        FILE* f = fopen(filename, "w");
        fputs(new_content, f);
        fclose(f);

    }

    return 0;
}