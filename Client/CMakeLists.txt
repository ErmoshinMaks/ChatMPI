cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Client)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

link_directories(${PROJECT_SOURCE_DIR}/lib/xtea3)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/threadsqueue.hpp
  src/mainwindow.cpp
  src/ClientDTO.h
  src/cripto.cpp

  src/mainwindow.ui
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt5::Core Qt5::Widgets pthread)

target_link_libraries(${PROJECT_NAME} PRIVATE xtea3)
