cmake_minimum_required(VERSION 3.13)  
project(wsr_sdk_server)               
set(CMAKE_CXX_STANDARD 20)            

include_directories(./boost_1_77_0)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_library(LIBRT rt)
add_compile_options(-g)

set(SOURCE_FILES server/server.cc
            main.cc)

add_executable(wsr_sdk_server_v1 ${SOURCE_FILES})
target_link_libraries(wsr_sdk_server_v1 Threads::Threads ${LIBRT})
