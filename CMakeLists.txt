cmake_minimum_required(VERSION 3.6)
project(Ast3roiDs)

# Activa símbolos de depuración.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Copia el directorio de recursos al directorio de los binarios
file(COPY ${PROJECT_SRC_DIR}Recursos DESTINATION .)

# Usa el estándar c++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

project(Ast3roiDs)
set(EXECUTABLE_NAME Ast3roiDs)
set(SOURCE_FILES main.cpp Graficos/Nave.hpp Graficos/Nave.cpp)
set(SFML_ROOT "C:/Program Files (x86)/SFML")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Detecta y linkea SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
