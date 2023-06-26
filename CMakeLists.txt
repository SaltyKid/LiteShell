cmake_minimum_required(VERSION 3.0)
project(LiteShell)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

set(CMAKE_BUILD_TYPE Release)
# set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_DEBUG "-g -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
set(CMAKE_C_FLAGS_RELEASE "-Os -DNDEBUG -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG -Wall")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)


if(WIN32)
set(CMAKE_C_COMPILER "D:/mingw/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "D:/mingw/bin/g++.exe")
else()
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
endif()

aux_source_directory(./LiteShell DIR_LITESHELL_SRCS)
aux_source_directory(./examples DIR_EXAMPLES_SRCS)
set(
    DIR_SRCS
    ${DIR_LITESHELL_SRCS}
    ${DIR_EXAMPLES_SRCS}
)

# include path
include_directories(LiteShell examples examples/logger)

# Target
add_executable(lite_shell ${DIR_SRCS})

