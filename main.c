#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "libinv-d/http_request.h"
#include "libinv-d/write_file.h"
#include "libinv-d/upload_file.h"

char* get_filename(char* name, short bool)
{
    char* filename = malloc(sizeof(char) * 16);
    time_t now = time(NULL);
    struct tm *tm_struct = localtime(&now);

    int month = tm_struct->tm_mon+bool;
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

    if (argc < 3) {
        fprintf( stderr, "Not enough arguments !\n");
        exit(1);
    }

    id = strtol(argv[1], &ptr, 10);

    if (strlen(ptr) != 5 || id == 0) {
        fprintf( stderr, "Not a valid warehouse name !\n");
        exit(1);
    }

    if (strcmp(argv[2], "monthly") == 0) {

        filename = get_filename(argv[1], 0);
        upload_file(filename, id);
    } else if (strcmp(argv[2], "daily") == 0) {

        filename = get_filename(argv[1], 1);
        result = do_request(id);
        check_output(result); // if result = "0", then it's free here then exit

        write_file(result, filename); // Those 2 values are free here
    }



    return 0;
}