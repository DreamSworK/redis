cmake_minimum_required(VERSION 3.10)
project(REDIS)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)

set(HIREDIS_DIR "${PROJECT_SOURCE_DIR}/hiredis")
set(HIREDIS_INCLUDE "${HIREDIS_DIR}")
set(HIREDIS_SOURCES
        "${HIREDIS_DIR}/async.c"
        "${HIREDIS_DIR}/sds.c"
        "${HIREDIS_DIR}/net.c"
        "${HIREDIS_DIR}/hiredis.c"
        "${HIREDIS_DIR}/read.c"
        "${HIREDIS_DIR}/dict.c")

include_directories(SYSTEM ${HIREDIS_INCLUDE})

add_executable(REDIS main.cpp ${HIREDIS_SOURCES})