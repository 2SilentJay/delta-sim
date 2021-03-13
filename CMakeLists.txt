cmake_minimum_required(VERSION 3.17)
project(dlogic)

##################
# common section #
##################

set(CMAKE_CXX_STANDARD 14)
set(DEBUG_LEVEL "-g3")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_LEVEL} -std=gnu++0x -mssse3 -Wall")

set(COMMON_UTILS_SRC "${PROJECT_SOURCE_DIR}/../common-utils/src")
message("cm=${COMMON_UTILS_SRC}")
include_directories("${COMMON_UTILS_SRC}/lib")

################
# applications #
################

set(TTT_NAME "ttt")
set(DLOGIC_NAME "dlogic")
set(TTGEN_NAME "ttgen")

add_executable(${TTT_NAME} src/app/ttt.cpp)

add_executable(${DLOGIC_NAME} src/main.cpp)

add_executable(${TTGEN_NAME} src/ttgen.cpp)

#target_link_libraries(${dlogic})
