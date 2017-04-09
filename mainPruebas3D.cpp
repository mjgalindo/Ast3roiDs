#include <iostream>
#include <GL/glew.h>
#include "Graficos3D/Asteroide3D.hpp"
#include "Graficos3D/Nave3D.hpp"

using namespace std;
using namespace sf;

int main() {
    // Carga un solo asteroide
    Asteroide3D testAsteroide;
    Nave3D testNave;

    // create the window
    sf::ContextSettings configuracion;
    configuracion.depthBits = 24;
    configuracion.stencilBits = 8;
    configuracion.antialiasingLevel = 0;
    configuracion.majorVersion = 3;
    configuracion.minorVersion = 3;

    RenderWindow ventana(sf::VideoMode::getDesktopMode(), "OpenGL", sf::Style::Default, configuracion);
    ventana.setFramerateLimit(60);

    glewInit();
    glViewport(0, 0, ventana.getSize().x, ventana.getSize().y);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);

    ventana.setActive(true);

    GLenum status = glewInit();
    if (status != GLEW_OK) {
        cerr << "Glew failed to init" << endl;
    }

    sf::Vector2u wsize = ventana.getSize();
    glViewport(0, 0, wsize.x, wsize.y);
    glMatrixMode(GL_PROJECTION);
    GLfloat ratio = static_cast<float>(ventana.getSize().x) / ventana.getSize().y;
    gluPerspective(60, ratio, 0.1f, 512.f);
    Vector3f posCamara = {0, 0, -6};
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

        // Limpia la ventana (no en negro para detectar posibles formas 3D sin color)
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dibuja todos los elementos
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
        glTranslatef(posCamara.x, posCamara.y, posCamara.z);
        //ventana.draw(testAsteroide);
        ventana.draw(testNave);

        glPopMatrix();
        ventana.display();
    }

    return 0;
}