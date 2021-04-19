//
// Created by user0 on 4/19/21.
//

#include "upload_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <sys/stat.h>

size_t read_data (char *bufptr, size_t size, size_t nitems, void *userp)
{
    size_t read;
    read = fread(bufptr, size, nitems, userp);
    return read;
}

void upload_file(char* filename, const long id)
{
    CURL *curl;
    CURLcode res;
    struct stat file_info;
    double speed_upload, total_time;
    FILE *fd;

    char *url = "http://192.168.1.16/php-back/Inventory/%ld";

    fd = fopen(filename, "rb"); /* open file to upload */
    if(!fd)
    {
        fprintf( stderr, "File not found !\n");
        exit(1);
    }

    curl = curl_easy_init();
    if(curl)
    {
        /* upload to this place */
        curl_easy_setopt(curl, CURLOPT_URL, url);

        /* tell it to "upload" to the URL */
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_data);

        /* set where to read from (on Windows you need to use READFUNCTION too) */
        curl_easy_setopt(curl, CURLOPT_READDATA, fd);

        /* enable verbose for easier tracing */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        /* now extract transfer info */
        curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &speed_upload);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);

        printf("Speed: %.3f bytes/sec during %.3f seconds\n", speed_upload, total_time);

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
}