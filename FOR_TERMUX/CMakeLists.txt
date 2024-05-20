cmake_minimum_required(VERSION 3.5)
project(encryption LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${PROJECT_SOURCE_DIR}/lib)
# find_package(xtea3)

add_executable(${PROJECT_NAME}
  main.cpp
)
find_library(${PROJECT_NAME} xtea3)
# target_link_libraries(${PROJECT_NAME} PRIVATE libxtea3)


# add_executable(test main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE xtea3)