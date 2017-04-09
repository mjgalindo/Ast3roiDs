#ifndef AST3ROIDS_ASTEROIDE3D_HPP
#define AST3ROIDS_ASTEROIDE3D_HPP

#include "Malla.hpp"

class Asteroide3D : public Malla {
public:
    Asteroide3D();

    void mover();

private:
    const float VELOCIDAD_MAX = 0.2f;

    sf::Vector3f velocidad;
};


#endif //AST3ROIDS_ASTEROIDE3D_HPP
