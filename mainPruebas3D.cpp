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

long int puntuacion = 0;

/**
 * De: https://guidedhacking.com/showthread.php?6588-OpenGL-Draw-a-crosshair
 * Dibuja una cruz en el centro de la ventana.
 */
void dibujaCruz(sf::Vector2u tamVentana) {
    glPushMatrix();
    glViewport(0, 0, tamVentana.x, tamVentana.y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, tamVentana.x, tamVentana.y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3ub(240, 240, 240);//white
    glLineWidth(2.0);
    glBegin(GL_LINES);
    //horizontal line
    glVertex2i(tamVentana.x / 2 - 7, tamVentana.y / 2);
    glVertex2i(tamVentana.x / 2 + 7, tamVentana.y / 2);
    glEnd();
    //vertical line
    glBegin(GL_LINES);
    glVertex2i(tamVentana.x / 2, tamVentana.y / 2 + 7);
    glVertex2i(tamVentana.x / 2, tamVentana.y / 2 - 7);
    glEnd();

    glPopMatrix();
}

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
    unique_ptr<ControladorSonido> csonido{new ControladorSonido};

    // Inicializa shaders y texturas.
    ControladorShaders::getShader(ControladorShaders::SIMPLE)->bind();
    ControladorShaders::getShader(ControladorShaders::SIMPLE)->setDireccionLuz({0.0f, -0.75f, 0.25f});
    ControladorShaders::getShader(ControladorShaders::BRILLO)->bind();
    ControladorShaders::getShader(ControladorShaders::BRILLO)->setDireccionLuz({0.0f, -0.75f, 0.25f});

    // Carga asteroides para ver como se mueve la nave
    vector<Asteroide3D> asteroides;
    for (int i = 0; i < 100; i++)
        asteroides.emplace_back(csonido.get());

    Nave3D testNave(csonido.get(), &puntuacion);

    Ovni3D ovni(csonido.get());

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
        for (Asteroide3D &asteroide : asteroides)
            asteroide.actualizar();

        sf::Vector2i posCursor = sf::Mouse::getPosition(ventana);

        testNave.actualizar(asteroides, {posCursor.x - WIDTH / 2, posCursor.y - HEIGHT / 2});
        if (ventana.hasFocus()) sf::Mouse::setPosition({WIDTH / 2, HEIGHT / 2}, ventana);

        ovni.actualizar(asteroides, testNave);

        if(testNave.getVidas()<0){
            running=false;
        }

        // Actualiza la cámara con respecto a la posicion de la nave utilizando su matriz modelo-mundo.
        glm::mat4 modeloNave = testNave.pos.matrizModelo();
        camara.pos = glm::vec3(modeloNave * glm::vec4(-30.0f, 4.0f, 0.0f, 1.0f));
        camara.forward = glm::vec3(modeloNave * testNave.DIRECCION_FRENTE_INICIAL);

        // Mantiene el vector up de la cámara apuntando hacia arriba
        camara.up = glm::cross(camara.forward, // Implementación tentativa, hasta que no gire bien la nave...
                               glm::vec3(modeloNave * glm::vec4{0.0f, 0.0f, -1.0f, 0.0f}));

        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        ventana.clear({0.1f, 0.1f, 0.1f});

        // Dibuja todos los elementos
        for (const Asteroide3D &asteroide : asteroides)
            asteroide.dibujar(ventana, camara);

        testNave.dibujar(ventana, camara);
        ovni.dibujar(ventana, camara);

        // Muestra el fotograma
        ventana.display();
    }

    return 0;
}