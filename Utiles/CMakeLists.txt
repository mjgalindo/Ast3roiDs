set(SOURCE_FILES entrenarDisparos.cpp ../ControladorSonido.hpp ../ControladorSonido.cpp ../Estados.hpp ../Colisiones.hpp ../Colisiones.cpp ../Graficos/Triangular.hpp ../Graficos/Triangular.cpp ../Graficos/Circular.hpp ../Graficos/Circular.cpp ../Graficos/Disparo.hpp ../Graficos/Disparo.cpp ../Graficos/Nave.hpp ../Graficos/Nave.cpp ../Graficos/Asteroide.cpp ../Graficos/Asteroide.hpp ../Graficos/Ovni.cpp ../Graficos/Ovni.hpp entrenarDisparos.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

add_executable(entrenar ${SOURCE_FILES})
target_link_libraries(entrenar ${SFML_LIBRARIES})
target_link_libraries(entrenar neural)