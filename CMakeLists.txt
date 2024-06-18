cmake_minimum_required(VERSION 3.21)

project("tanks" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory("dependencies/SDL")
list(APPEND PROJECT_INCLUDE_DIRS "dependencies/SDL/include")
list(APPEND PROJECT_LINK_LIBRARIES SDL3::SDL3-shared)

add_subdirectory("dependencies/glm")
list(APPEND PROJECT_INCLUDE_DIRS "dependencies/glm")
list(APPEND PROJECT_LINK_LIBRARIES glm::glm)

file(GLOB_RECURSE PROJECT_SOURCES "sources/*")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME}
		PUBLIC ${PROJECT_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
		PUBLIC ${PROJECT_LINK_LIBRARIES})
