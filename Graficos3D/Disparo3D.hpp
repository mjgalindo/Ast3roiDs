#ifndef AST3ROIDS_DISPARO3D_HPP
#define AST3ROIDS_DISPARO3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Elemento3D.hpp"

class Disparo3D : public Elemento3D {
public:
    Disparo3D(glm::vec3 direccion, glm::vec3 posicion);

    void actualizar();

    const float VELOCIDAD_BASE = 5.0f;

    glm::vec3 velocidad;
};


#endif //AST3ROIDS_DISPARO3D_HPP
