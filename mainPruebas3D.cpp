#include <iostream>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"
#include "Graficos3D/Ovni3D.hpp"
#include "Util3D/Ventana3D.hpp"
#include "Util3D/ControladorTexturas.hpp"
#include "Util3D/ControladorShaders.hpp"

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
    ventana.setMouseCursorVisible(false);
    ventana.setMouseCursorGrabbed(true);

    // Inicializa los modelos 3D y las texturas. Esto objetos solo existe para controlar
    // la creacion y destrucción de recursos.
    ControladorModelos __controladorModelos;
    ControladorTexturas __controladorTexturas;
    ControladorShaders __controladorShaders;

    // Inicializa shaders y texturas.
    ControladorShaders::getShader(ControladorShaders::SIMPLE)->bind();
    ControladorShaders::getShader(ControladorShaders::SIMPLE)->setDireccionLuz({0.0f, -0.75f, 0.25f});
    ControladorShaders::getShader(ControladorShaders::BRILLO)->bind();
    ControladorShaders::getShader(ControladorShaders::BRILLO)->setDireccionLuz({0.0f, -0.75f, 0.25f});

    // Carga asteroides para ver como se mueve la nave
    vector<Asteroide3D> asteroides;
    for (int i = 0; i < 100; i++)
        asteroides.emplace_back();

    Nave3D testNave;

    Ovni3D ovni;

    Camara camara({0.0f, 0.0f, 0.0f}, Ventana3D::FOV, (float) ventana.getSize().x / (float) ventana.getSize().y,
                  Ventana3D::Z_NEAR, Ventana3D::Z_FAR);

    bool running = true;

    while (running) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        testNave.disparar();
                        break;
                    }
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
            asteroide.actualizar();

        sf::Vector2i posCursor = sf::Mouse::getPosition(ventana);

        testNave.actualizar(asteroides, {posCursor.x - WIDTH / 2, posCursor.y - HEIGHT / 2});
        sf::Mouse::setPosition({WIDTH / 2, HEIGHT / 2}, ventana);
        ovni.actualizar(asteroides);

        // Actualiza la cámara con respecto a la posicion de la nave utilizando su matriz modelo-mundo.
        glm::mat4 modeloNave = testNave.pos.matrizModelo();
        camara.pos = glm::vec3(modeloNave * glm::vec4(-30.0f, 7.0f, 0.0f, 1.0f));
        camara.forward = glm::vec3(modeloNave * testNave.DIRECCION_INICIAL);

        // Mantiene el vector up de la cámara apuntando hacia arriba
        camara.up = glm::cross(camara.forward, // Implementación tentativa, hasta que no gire bien la nave...
                               glm::vec3(modeloNave * glm::vec4{0.0f, 0.0f, -1.0f, 0.0f}));

        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        ventana.clear({0.1f, 0.1f, 0.1f});


        cout << "Numero de Asteroides: " << asteroides.size() << endl;
        // Dibuja todos los elementos
        for (auto asteroide : asteroides)
            asteroide.dibujar(ventana, camara);

        testNave.dibujar(ventana, camara);
        ovni.dibujar(ventana, camara);
        // Muestra el fotograma
        ventana.display();
    }

    return 0;
}