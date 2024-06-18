cmake_minimum_required(VERSION 3.21)
project("tanks" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("dependencies/SDL")
list(APPEND TANKS_INCLUDE_DIRS "dependencies/SDL/include")
list(APPEND TANKS_LINK_LIBRARIES SDL3::SDL3-shared)

set(TANKS_EXECUTABLE "tanks")

file(GLOB_RECURSE TANKS_SOURCES "sources/*")
add_executable(${TANKS_EXECUTABLE} ${TANKS_SOURCES})
target_include_directories(${TANKS_EXECUTABLE} PUBLIC
        ${TANKS_INCLUDE_DIRS})
target_link_libraries(${TANKS_EXECUTABLE} PUBLIC
        ${TANKS_LINK_LIBRARIES})
