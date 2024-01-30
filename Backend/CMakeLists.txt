cmake_minimum_required(VERSION 3.22)
project(Backend)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})


add_executable(Backend main.cpp)

add_executable(Initialize_Database Database/ddl.cpp)

target_link_libraries(Initialize_Database ${SQLite3_LIBRARIES})