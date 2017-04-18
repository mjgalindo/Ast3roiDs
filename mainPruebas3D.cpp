#include <iostream>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Util3D/Ventana3D.hpp"
#include "Util3D/ControladorTexturas.hpp"

using namespace std;
using namespace sf;

#define WIDTH 1700
#define HEIGHT 1100

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
    shaderPrincipal.bind();
    shaderPrincipal.setDireccionLuz({0.0f, -0.75f, 0.25f});

    // Carga asteroides para ver como se mueve la nave
    vector<Asteroide3D> asteroides;
    for (int i = 0; i < 100; i++)
        asteroides.emplace_back(&shaderPrincipal);

    Nave3D testNave(&shaderPrincipal);

    Camara camara({0.0f, 0.0f, 0.0f}, Ventana3D::FOV, (float) ventana.getSize().x / (float) ventana.getSize().y,
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
        for (auto asteroide : asteroides)
            asteroide.mover();

        testNave.actualizar();

        // Actualiza la cámara con respecto a la posicion de la nave utilizando su matriz modelo-mundo.
        glm::mat4 modeloNave = testNave.pos.matrizModelo();
        glm::vec4 posCamara = modeloNave * glm::vec4(-16.0f, 1.0f, 0.0f, 1.0f);
        glm::vec4 dirCamara = modeloNave * testNave.DIRECCION_INICIAL;
        camara.pos = glm::vec3(posCamara);
        camara.forward = glm::vec3(dirCamara);

        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        ventana.clear({0.1f, 0.1f, 0.1f});

        // Dibuja todos los elementos
        for (auto asteroide : asteroides)
            ventana.draw(asteroide.predibujado(camara));

        ventana.draw(testNave.predibujado(camara));

        // Muestra el fotograma
        ventana.display();
    }

    return 0;
}