cmake_minimum_required(VERSION 3.21)

project("tanks" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib_d")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/lib_d")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin_d")

find_package(OpenGL REQUIRED)
list(APPEND PROJECT_INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS})
list(APPEND PROJECT_LINK_LIBRARIES ${OPENGL_LIBRARIES})

list(APPEND PROJECT_INCLUDE_DIRS "dependencies/glad/include")

add_subdirectory("dependencies/glm")
list(APPEND PROJECT_INCLUDE_DIRS "dependencies/glm")
list(APPEND PROJECT_LINK_LIBRARIES glm::glm)

add_subdirectory("dependencies/SDL")
list(APPEND PROJECT_INCLUDE_DIRS "dependencies/SDL/include")
list(APPEND PROJECT_LINK_LIBRARIES SDL3::SDL3-shared)

file(GLOB_RECURSE PROJECT_SOURCES "sources/*")
list(APPEND PROJECT_SOURCES "dependencies/glad/src/glad.c")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME}
		PUBLIC ${PROJECT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
		PUBLIC ${PROJECT_LINK_LIBRARIES})

file(GLOB PROJECT_SHADERS "shaders/*")
foreach (FILE_PATH ${PROJECT_SHADERS})
    get_filename_component(FILE_NAME ${FILE_PATH} NAME)
    configure_file(${FILE_PATH}
    "${CMAKE_BINARY_DIR}/shaders/${FILE_NAME}" COPYONLY)
endforeach ()
