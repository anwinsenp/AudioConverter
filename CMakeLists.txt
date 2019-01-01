cmake_minimum_required(VERSION 2.8.12)

project(WavToMP3Converter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable (${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/directory.cpp)

#find_package(Qt5Core)


#target_link_libraries(${PROJECT_NAME} Qt5::Core)
