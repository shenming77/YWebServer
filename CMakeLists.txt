message("* * * * * * * * * *  Y_WebServer * * * * * * * * * * * * * * *")

cmake_minimum_required(VERSION 3.1.0)

project(Y_WebServer LANGUAGES CXX)

# 默认使用C++14版本，推荐使用C++17版本。不支持C++11以下版本
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -fPIC")
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")

find_package(Threads REQUIRED)


include_directories (
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

link_directories(
)


file(GLOB_RECURSE LibSource src/*.cpp)
add_library(utils ${LibSource})
target_link_libraries(utils Threads::Threads mysqlclient)
# add_dependencies(utils)

add_executable(y_server app/main.cpp)
target_link_libraries(y_server utils)

# add_executable(thread_gtest test/threadpool_gtest.cpp)
# target_link_libraries(thread_gtest gtest utils)

# add_executable(thread_test test/threadpool_test.cpp)
# target_link_libraries(thread_test  utils)


# enable_testing()
# add_test(NAME thread_pool_test COMMAND thread_gtest)

# # 使用 Valgrind 的测试
# add_test(NAME ValgrindTest1 
#          COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:y_thread>)
         
# add_test(NAME ValgrindTest2 
#          COMMAND valgrind --leak-check=full --error-exitcode=1 $<TARGET_FILE:thread_test>)
