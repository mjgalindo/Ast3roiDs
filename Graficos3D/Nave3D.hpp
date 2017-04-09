#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Malla.hpp"

class Nave3D : public Malla {
public:
    Nave3D();

    void mover();

private:

    const float VELOCIDAD_MAX = 0.6f;

    sf::Vector3f velocidad;
};


#endif //AST3ROIDS_NAVE3D_HPP
