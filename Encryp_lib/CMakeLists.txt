# cmake_minimum_required( VERSION 3.4.0 )

# project( shared_lib CXX )			

# set( SOURCE_LIB xtea3.cpp )		

# set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )

# add_library( xtea3 SHARED ${SOURCE_LIB} )	

# cmake_minimum_required(VERSION 3.5)
# project(test LANGUAGES CXX)
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# include(GenerateExportHeader)
# add_library(xtea3 SHARED xtea3.cpp)
# generate_export_header(xtea3)
# target_include_directories(xtea3 PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})
# add_executable(test main.cpp)
# target_link_libraries(test PRIVATE power)

cmake_minimum_required( VERSION 3.5 )
project(xtea3)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

add_library(${PROJECT_NAME} STATIC)


target_sources(${PROJECT_NAME}
    PRIVATE
        src/xtea3.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# note that it is not CMAKE_INSTALL_PREFIX we are checking here
if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX is not set\n"
        "Default value: ${CMAKE_INSTALL_PREFIX}\n"
        "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
        "${CMAKE_SOURCE_DIR}/install"
        CACHE PATH "Where the library will be installed to" FORCE
    )
else()
    message(
        STATUS
        "CMAKE_INSTALL_PREFIX was already set\n"
        "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

# without it public headers won't get installed
set(public_headers
    include/xtea3.h
)
# note that ${public_headers} has to be in quotes
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")



# # for CMAKE_INSTALL_INCLUDEDIR definition
# include(GNUInstallDirs)

# # the variant with PUBLIC_HEADER property unfortunately does not preserve the folder structure
# #set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
# # so instead we iterate through public headers and install them "manually"
# foreach(header ${public_headers})
#     file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}" "${header}")
#     get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
#     install(
#         FILES ${header}
#         DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
#     )
# endforeach()

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")


# if you haven't included it already
# definitions of CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR and others
include(GNUInstallDirs)

# install the target and create export-set
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"
    # these get default values from GNUInstallDirs, no need to set them
    #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    # except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/SomeLibrary
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)


# install(
#     TARGETS targets... [EXPORT <export-name>]
#     [RUNTIME_DEPENDENCIES args...|RUNTIME_DEPENDENCY_SET <set-name>]
#     [
#         [
#             ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|PRIVATE_HEADER|PUBLIC_HEADER|RESOURCE
#         ]
#         [DESTINATION <dir>]
#         [PERMISSIONS permissions...]
#         [CONFIGURATIONS [Debug|Release|...]]
#         [COMPONENT <component>]
#         [NAMELINK_COMPONENT <component>]
#         [OPTIONAL] [EXCLUDE_FROM_ALL]
#         [NAMELINK_ONLY|NAMELINK_SKIP]
#     ] [...]
#     [INCLUDES DESTINATION [<dir> ...]]
# )

# set_target_properties(some::SomeLibrary PROPERTIES
#   INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
# )