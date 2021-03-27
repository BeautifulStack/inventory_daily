#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {

    while (1){

        // get time in hour and minute
        time_t now = time(NULL);
        struct tm *tm_struct = localtime(&now);
        int hour = tm_struct->tm_hour;
        int minutes = tm_struct->tm_min;

        // backup time
        if ((hour == 23 || hour == 11) && (minutes == 59)){

            // to work only once in a minute
            sleep(60);

            // the work todo
            FILE* f = fopen("test.txt", "a");
            fprintf(f, "%d:%d\n", hour, minutes);
            fclose(f);
        }
    }

    return 0;
}