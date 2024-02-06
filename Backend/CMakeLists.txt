cmake_minimum_required(VERSION 3.22)
project(Backend)

set(CMAKE_CXX_STANDARD 17)

find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${SQLite3_INCLUDE_DIRS})


add_executable(
        Backend Database/constants.h
        Database/dml.cpp
        Database/dml.h
        main.cpp
        Database/dql.cpp
        Database/dql.h
)

add_executable(
        Initialize_Database Database/constants.h
        Database/ddl.cpp
)

target_link_libraries(Initialize_Database ${SQLite3_LIBRARIES})
target_link_libraries(Backend ${SQLite3_LIBRARIES} OpenSSL::Crypto)