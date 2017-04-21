#ifndef AST3ROIDS_ASTEROIDE3D_HPP
#define AST3ROIDS_ASTEROIDE3D_HPP

#include "Elemento3D.hpp"

class Asteroide3D : public Elemento3D {
public:
    Asteroide3D();
    void actualizar();

private:
    const float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
};


#endif //AST3ROIDS_ASTEROIDE3D_HPP
