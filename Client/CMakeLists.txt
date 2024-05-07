cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME Client)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Sql Qml REQUIRED)


add_executable(${PROJECT_NAME}
  src/main.cpp
  qml/qml.qrc
  
  src/sqlcontactmodel.cpp 
  src/logmodel.cpp 
  src/sqlconversationmodel.cpp 
  # src/dialog.cpp
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql  Qt5::Qml)
