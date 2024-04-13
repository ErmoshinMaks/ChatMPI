cmake_minimum_required(VERSION 3.5)

project(ChatMPI LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        REQUIRED)


add_executable(ChatMPI
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
  )


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Database)


include_directories(${Qt5_INCLUDE_DIR})

target_link_libraries(ChatMPI
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Engine
        Database
        )



#target_link_libraries(ChatMPI PRIVATE Qt5::Widgets)
