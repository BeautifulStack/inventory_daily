#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "libinv-d/daily_run.h"
#include "libinv-d/http_request.h"

int main(int argc, char** argv)
{
    long id;
    char* ptr;
    FILE* f;

    if (argc < 2) {
        fprintf( stderr, "No id warehouse provided !\n");
        exit(1);
    }

    id = strtol(argv[1], &ptr, 10);

    f = do_request(id);

    // main loop
    //daily_run();

    return 0;
}