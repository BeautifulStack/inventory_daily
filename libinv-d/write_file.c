//
// Created by user0 on 4/17/21.
//

#include <stdio.h>
#include <unistd.h>
#include "write_file.h"

int write_file(FILE* f, char* filename)
{

    if(access(filename, F_OK) == 0 ) {
        // file exists
    }

}