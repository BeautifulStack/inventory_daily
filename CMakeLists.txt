cmake_minimum_required(VERSION 3.16)
project(inventory_daily C)

set(CMAKE_C_STANDARD 99)

add_executable(inventory_daily main.c libinv-d/http_request.c libinv-d/http_request.h libinv-d/write_file.c libinv-d/write_file.h libinv-d/upload_file.c libinv-d/upload_file.h)
target_link_libraries(inventory_daily curl)