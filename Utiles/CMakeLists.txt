set(SOURCE_FILES EntrenarRed.cpp ../Colisiones.hpp ../Colisiones.cpp ../Graficos/Circular.hpp ../Graficos/Circular.cpp ../Graficos/Disparo.hpp ../Graficos/Disparo.cpp ../Graficos/Nave.hpp ../Graficos/Nave.cpp ../Graficos/Asteroide.cpp ../Graficos/Asteroide.hpp ../Graficos/Ovni.cpp ../Graficos/Ovni.hpp)

add_executable(entrenar ${SOURCE_FILES})
target_link_libraries(entrenar ${SFML_LIBRARIES})
target_link_libraries(entrenar neural)