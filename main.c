#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "libinv-d/http_request.h"
#include "libinv-d/write_file.h"

char* get_filename(char* name)
{
    char* filename = malloc(sizeof(char) * 16);
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int month = tm_struct->tm_mon;
    int year = (tm_struct->tm_year+1900)%100;

    if (month < 10) {
        sprintf(filename, "data/%s0%d%d.xml", name, month, year);
    } else {
        sprintf(filename, "data/%s%d%d.xml", name, month, year);
    }

    return filename;
}

int main(int argc, char** argv)
{
    long id;
    char* ptr;
    char* result;
    char* filename;

    if (argc < 2) {
        fprintf( stderr, "No id warehouse provided !\n");
        exit(1);
    }

    id = strtol(argv[1], &ptr, 10);

    if (strlen(ptr) != 5) {
        fprintf( stderr, "Not a valid warehouse name !\n");
        exit(1);
    }

    result = do_request(id);
    //check_output(result); // if result = "0", then it's free here then exit

    filename = get_filename(argv[1]);

    write_file(result, filename); // Those 2 values are free here

    return 0;
}