cmake_minimum_required(VERSION 3.16)
project(prstd C)

set(CMAKE_C_STANDARD 11)

add_executable(prstd test.c array_list.h array_list.c container.c container.h iterator.c iterator.h priority_queue.c priority_queue.h hash_map.c hash_map.h)