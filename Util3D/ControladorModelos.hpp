#ifndef AST3ROIDS_CONTROLADORMODELOS_HPP
#define AST3ROIDS_CONTROLADORMODELOS_HPP

#include <GL/glew.h>
#include <array>

struct Modelo{
    enum
    {
        POSITION_VB = 0,
        TEXCOORD_VB = 1,
        NORMAL_VB = 2,
        INDEX_VB = 3,
        NUM_BUFFERS = 4
    };

    GLuint vertexArrayObject;
    GLuint vertexArrayBuffers[NUM_BUFFERS];
    unsigned int numTriangulos;
};

class ControladorModelos {
public:
    ControladorModelos();
    ~ControladorModelos();

    enum TipoModelo {
        ASTEROIDE = 0,
        NAVE,
        DISPARO,
        NUM_MODELOS
    };

    static Modelo getModelo(TipoModelo tipo);

private:
    static void cargaMalla(TipoModelo tipo);
};


#endif //AST3ROIDS_CONTROLADORMODELOS_HPP
