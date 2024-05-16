cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Server)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


find_package(Qt5 COMPONENTS
        Core
        Sql
        REQUIRED)


add_executable(${PROJECT_NAME}
    main.cpp
  )


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Database)


include_directories(${Qt5_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Sql
        Engine
        Database
        pthread
        )

