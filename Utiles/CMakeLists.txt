set(SOURCE_FILES entrenarDisparos.cpp ../ControladorSonido.hpp ../ControladorSonido.cpp ../Estados.hpp ../Colisiones.hpp ../Colisiones.cpp ../Graficos/Triangular.hpp ../Graficos/Triangular.cpp ../Graficos/Circular.hpp ../Graficos/Circular.cpp ../Graficos/Disparo.hpp ../Graficos/Disparo.cpp ../Graficos/Nave.hpp ../Graficos/Nave.cpp ../Graficos/Asteroide.cpp ../Graficos/Asteroide.hpp ../Graficos/Ovni.cpp ../Graficos/Ovni.hpp)

set(FUENTES_3D
        entrenarDisparos3D.cpp
        ../Graficos3D/Elemento3D.hpp
        ../Graficos3D/Elemento3D.cpp
        ../Graficos3D/Asteroide3D.hpp
        ../Graficos3D/Asteroide3D.cpp
        ../Graficos3D/Nave3D.hpp
        ../Graficos3D/Nave3D.cpp
        ../Graficos3D/Ovni3D.cpp
        ../Graficos3D/Ovni3D.hpp
        ../Graficos3D/Disparo3D.cpp
        ../Graficos3D/Disparo3D.hpp
        ../Util3D/Ventana3D.cpp
        ../Util3D/Ventana3D.hpp
        ../Util3D/Shader.hpp
        ../Util3D/Shader.cpp
        ../Util3D/Posicionamiento.hpp
        ../Util3D/Camara.hpp
        ../Util3D/Textura.cpp
        ../Util3D/Textura.hpp
        ../Util3D/ControladorModelos.cpp
        ../Util3D/ControladorModelos.hpp
        ../Util3D/ControladorTexturas.cpp
        ../Util3D/ControladorTexturas.hpp
        ../Util3D/ControladorShaders.cpp
        ../Util3D/ControladorShaders.hpp
        ../matematicas.hpp
        ../Estados.hpp
        ../Colisiones.hpp
        ../Colisiones.cpp
        ../ControladorSonido.cpp
        ../ControladorSonido.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

add_executable(entrenar ${SOURCE_FILES})
add_executable(entrenar3D ${FUENTES_3D})
target_link_libraries(entrenar ${SFML_LIBRARIES})
target_link_libraries(entrenar neural)


target_link_libraries(entrenar3D ${SFML_LIBRARIES}  ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} neural)