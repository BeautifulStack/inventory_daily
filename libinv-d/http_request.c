//
// Created by user0 on 4/17/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "http_request.h"

FILE* do_request(const long id)
{
    char url[64];
    CURL *curl;
    char result_curl;
    FILE* f;

    curl = curl_easy_init();
    if (curl) {

        sprintf(url, "http://192.168.1.16/php-back/Inventory/%ld", id);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        //set network option, provide the URL to use in the request

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //Set http option, follow HTTP 3xx redirects set long parameter to 1

        f = tmpfile();

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
        //Write output to result

        result_curl = curl_easy_perform(curl);
        //Perform the entire request in a blocking manner


        if (result_curl != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result_curl));

        curl_easy_cleanup(curl);

        return f;
    }

    return NULL;
}