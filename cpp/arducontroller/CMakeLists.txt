cmake_minimum_required(VERSION 2.8)

project(arducontroller)
set(SOURCES main.cpp arduserialstream.cpp arduinointerface.cpp)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries (${PROJECT_NAME} serial pthread)
