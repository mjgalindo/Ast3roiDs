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

    glMatrixMode(GL_PROJECTION);
    GLfloat ratio = static_cast<float>(wsize.x) / wsize.y;
    // Configura la camara con un FOV de 60º y no renderice elementos a una distancia menor que 0.1 ni mayor que 1024
    gluPerspective(FOV, ratio, Z_NEAR, Z_FAR);

    // TODO: Activar iluminación. Estos comandos "funcionan" pero las mallas pierden su color
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
}

void Ventana3D::clear(sf::Vector3f color) {
    glClearColor(color.x, color.y, color.z, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
