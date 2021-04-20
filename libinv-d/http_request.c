//
// Created by user0 on 4/17/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "http_request.h"

#define CHUNK 4096

char* result_global;
unsigned long size_global = 0;
unsigned long counter_global = 0;

// function called by curl to write into result string
static size_t write_result(void *ptr, size_t size, size_t nmemb, void *stream)
{
    if ((size*nmemb + counter_global) > size_global) {
        unsigned long tmp = ((size*nmemb) + counter_global) - size_global;
        size_global = size_global + tmp;
        result_global = realloc(result_global, size_global);
        if (result_global == NULL) {
            fprintf( stderr, "Failed to reallocate more memory to request result !\n");
            exit(1);
        }
    }
    strcat(result_global, ptr);
    counter_global = counter_global + (size*nmemb);
    return size*nmemb;
}

char* do_request(const long id)
{
    char url[64];
    CURL *curl;
    char result_curl;

    curl = curl_easy_init();
    if (curl) {

        sprintf(url, "http://192.168.1.16/php-back/Inventory/%ld", id);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        //set network option, provide the URL to use in the request

        result_global = strdup("");
        if (result_global == NULL) {
            fprintf( stderr, "Failed to allocate more memory to request result !\n");
            exit(1);
        }
        size_global = 1;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_result);
        //Write output to result

        result_curl = curl_easy_perform(curl);
        //Perform the entire request in a blocking manner


        if (result_curl != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result_curl));
            exit(1);
        }

        curl_easy_cleanup(curl);

        size_global = 0;
        counter_global = 0;
        return result_global;
    }

    return NULL;
}

int check_output(char* result)
{
    if (result == NULL) {
        fprintf( stderr, "Failed to do request !\n");
        free(result);
        exit(1);
    } else if (strcmp(result, "0") == 0) {
        printf("No import/export today !\n");
        free(result);
        exit(0);
    } else if (strcmp(result, "1") == 0) {
        fprintf( stderr, "Not a valid warehouse id !\n");
        free(result);
        exit(1);
    }
}