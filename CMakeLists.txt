cmake_minimum_required(VERSION 3.6)
project(Ast3roiDs)

# Activa símbolos de depuración.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Copia el directorio de recursos al directorio de los binarios
file(COPY ${PROJECT_SRC_DIR}Recursos DESTINATION .)

# Usa el estándar c++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -static -mwindows -pthread ")

project(Ast3roiDs)
set(EXECUTABLE_NAME Ast3roiDs)
set(SOURCE_FILES
		main.cpp
		Estados.hpp
		Colisiones.hpp
		Colisiones.cpp
		Graficos/Triangular.hpp
		Graficos/Triangular.cpp
		Graficos/Circular.hpp
		Graficos/Circular.cpp
		Graficos/Disparo.hpp
		Graficos/Disparo.cpp
		Graficos/Nave.hpp
		Graficos/Nave.cpp
		Graficos/Asteroide.cpp
		Graficos/Asteroide.hpp
		Graficos/Ovni.cpp
		Graficos/Ovni.hpp
		matematicas.hpp
		constantesGlobales.hpp
		ControladorSonido.cpp
		ControladorSonido.hpp
		Graficos/OvniInteligente.cpp
		Graficos3D/Nave3D.cpp
		Graficos3D/Nave3D.hpp
        Graficos3D/Elemento3D.cpp
        Graficos3D/Elemento3D.hpp
		Graficos3D/Asteroide3D.cpp
		Graficos3D/Asteroide3D.hpp
        Util3D/Ventana3D.cpp
        Util3D/Ventana3D.hpp)

set(PRUEBA3D prueba3D)
set(FUENTES_PRUEBA3D
		mainPruebas3D.cpp
        Graficos3D/Elemento3D.hpp
        Graficos3D/Elemento3D.cpp
		Graficos3D/Asteroide3D.hpp
		Graficos3D/Asteroide3D.cpp
		Graficos3D/Nave3D.hpp
		Graficos3D/Nave3D.cpp
		Util3D/Ventana3D.cpp
		Util3D/Ventana3D.hpp
		Util3D/Shader.hpp
		Util3D/Shader.cpp
		Util3D/Transformacion.hpp
		Util3D/Camara.hpp
		Util3D/Textura.cpp
		Util3D/Textura.hpp
		Util3D/obj_loader.h
		Util3D/obj_loader.cpp)

set(SFML_ROOT "C:/Program Files (x86)/SFML")

add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})
add_executable(${PRUEBA3D} ${FUENTES_PRUEBA3D})

find_package(OpenGL)
find_package(glew)
# Detecta y linkea SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
add_subdirectory(tinyobjloader)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} tinyobjloader)
	target_link_libraries(${PRUEBA3D} ${SFML_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} tinyobjloader)

endif()
