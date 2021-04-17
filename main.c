#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "libinv-d/daily_run.h"

int main() {

    // main loop
    daily_run();

    return 0;
}