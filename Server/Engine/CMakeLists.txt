cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Engine)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_library(Engine ${SOURCES})

target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(Engine Qt5::Core Qt5::Sql)


#add_executable(${PROJECT_NAME} ${source_list})
