#include <iostream>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Util3D/Ventana3D.hpp"

using namespace std;
using namespace sf;

#define WIDTH 800
#define HEIGHT 600

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
    Ventana3D ventana(sf::VideoMode(WIDTH, HEIGHT), "OpenGL", sf::Style::Close | sf::Style::Titlebar, configuracion,
                      60);

    // Inicializa shaders y texturas.
    vj::Shader shaderPrincipal(string("Recursos/Shaders/shaderBasico"));
    vj::Textura texturaBlanco(string("Recursos/Texturas/blanco.png"));
    vj::Textura texturaNave(string("Recursos/Texturas/naveUV_color_V2.png"));

    // Carga un solo asteroide
    Asteroide3D testAsteroide(&shaderPrincipal, &texturaNave);
    Nave3D testNave(&shaderPrincipal, &texturaBlanco);

    Camara camara({0, 0, -3.8f}, Ventana3D::FOV, (float) ventana.getSize().x / (float) ventana.getSize().y,
                  Ventana3D::Z_NEAR, Ventana3D::Z_FAR);

    bool running = true;
    while (running) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Add) {
                        camara.pos = {camara.pos.x, camara.pos.y, camara.pos.z + 0.05f};
                        break;
                    } else if (event.key.code == sf::Keyboard::Subtract) {
                        camara.pos = {camara.pos.x, camara.pos.y, camara.pos.z - 0.05f};
                        break;
                    } else if (event.key.code != sf::Keyboard::Escape) { break; }
                case sf::Event::Closed:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        // Mueve todos los elementos
        // testNave.mover();
        // testAsteroide.mover();
        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        ventana.clear({0.2f, 0.2f, 0.2f});
        // Dibuja todos los elementos
        //ventana.draw(testAsteroide.predibujado(camara));
        ventana.draw(testNave.predibujado(camara));

        ventana.display();
    }

    return 0;
}