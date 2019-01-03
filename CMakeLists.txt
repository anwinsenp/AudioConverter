cmake_minimum_required(VERSION 2.8.12)

project(AudioConverter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(/Users/anwin/Downloads/lame-3.99.5/include)

find_library(LIBLAME libmp3lame.a)

add_executable (${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/directory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mp3encoder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/converter.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBLAME} pthread)

#find_package(Qt5Core)


#target_link_libraries(${PROJECT_NAME} Qt5::Core)
