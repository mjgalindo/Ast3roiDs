#include <iostream>
#include "Ventana3D.hpp"
#include <GL/glew.h>

using namespace std;

Ventana3D::Ventana3D(sf::VideoMode videoMode, std::string title, unsigned int style, sf::ContextSettings settings,
                     unsigned int framerateLimit) : RenderWindow(videoMode, title, style, settings) {
    setFramerateLimit(framerateLimit);

    // Carga las funciones de OpenGL utilizando glew
    GLenum status = glewInit();
    if (status != GLEW_OK) {
        cerr << "Glew no ha podido inicializarse" << endl;
    }

    sf::Vector2u wsize = getSize();

    glViewport(0, 0, wsize.x, wsize.y);
    // Activa test de profundidad para ocluir triangulos que se encuentran detrás de otros.
    glEnable(GL_DEPTH_TEST);
    setActive(true);

    // TODO: Activar iluminación. Estos comandos "funcionan" pero las mallas pierden su color
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
}

void Ventana3D::clear(sf::Vector3f color) {
    glClearColor(color.x, color.y, color.z, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
