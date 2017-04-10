#include <iostream>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Graficos3D/Ventana3D.hpp"

using namespace std;
using namespace sf;

int main() {
    // Configura la ventana
    sf::ContextSettings configuracion;
    configuracion.depthBits = 24;
    configuracion.stencilBits = 8;
    configuracion.antialiasingLevel = 2;
    configuracion.majorVersion = 3;
    configuracion.minorVersion = 3;

    // Crea la ventana. El constructor carga las funciones de OpenGL y llama a glewInit() por lo que esto se debe
    // hacer al principio.
    Ventana3D ventana(sf::VideoMode::getDesktopMode(), "OpenGL", sf::Style::Default, configuracion, 60);

    // Carga un solo asteroide
    Asteroide3D testAsteroide;
    Nave3D testNave;

    bool running = true;

    while (running) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code != sf::Keyboard::Escape) { break; }
                case sf::Event::Closed:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        // Mueve todos los elementos
        testNave.mover();
        testAsteroide.mover();
        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        ventana.clear({0.1f, 0.1f, 0.1f});

        // Dibuja todos los elementos
        ventana.draw(testAsteroide);
        ventana.draw(testNave);

        ventana.display();
    }

    return 0;
}