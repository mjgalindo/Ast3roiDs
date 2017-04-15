#include <iostream>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Util3D/Ventana3D.hpp"
#include "Util3D/ControladorTexturas.hpp"

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

    // Inicializa los modelos 3D y las texturas. Esto objetos solo existe para controlar
    // la creacion y destrucción de recursos.
    ControladorModelos __controladorModelos;
    ControladorTexturas __controladorTexturas;

    // Inicializa shaders y texturas.
    vj::Shader shaderPrincipal(string("Recursos/Shaders/shaderBasico"));

    // Carga un solo asteroide
    Asteroide3D testAsteroide(&shaderPrincipal);
    Nave3D testNave(&shaderPrincipal);

    Camara camara({0, 0, -7.f}, Ventana3D::FOV, (float) ventana.getSize().x / (float) ventana.getSize().y,
                  Ventana3D::Z_NEAR, Ventana3D::Z_FAR);

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
        testAsteroide.mover();
        testNave.actualizar();

        // Actualiza la cámara con respecto a la posicion de la nave.
        // TODO: Controlar giros de la nave: la cámara también debe girar
        glm::vec3 posNave, rotNave;
        testNave.posiciones(posNave, rotNave);
        camara.pos = {posNave.x, posNave.y + 1.0f, posNave.z - 8.0f};

        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        ventana.clear({0.2f, 0.2f, 0.2f});

        // Dibuja todos los elementos
        ventana.draw(testAsteroide.predibujado(camara));
        ventana.draw(testNave.predibujado(camara));

        // Muestra el fotograma
        ventana.display();
    }

    return 0;
}