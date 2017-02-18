cmake_minimum_required(VERSION 3.6)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Use the c++17 standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(Ast3roiDs)
set(EXECUTABLE_NAME Ast3roiDs)
set(SOURCE_FILES main.cpp Graficos/Grafico.hpp Graficos/Grafico.cpp)
set(SFML_ROOT "C:/Program Files (x86)/SFML")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
