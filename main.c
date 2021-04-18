#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "libinv-d/daily_run.h"
#include "libinv-d/http_request.h"
#include "libinv-d/write_file.h"



int main(int argc, char** argv)
{
    long id;
    char* ptr;
    FILE* f;
    char* result;

    if (argc < 2) {
        fprintf( stderr, "No id warehouse provided !\n");
        exit(1);
    }

    id = strtol(argv[1], &ptr, 10);

    result = do_request(id);
    check_output(result); // if result = "0", then it's free here then exit

    printf("%s", result);

    free(result);

    //if (write_file(f, "mm"))

    // main loop
    //daily_run();

    return 0;
}