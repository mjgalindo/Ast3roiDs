#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Elemento3D.hpp"

class Nave3D : public Elemento3D {
public:
    Nave3D(vj::Shader *shader);

    void actualizar();

    const float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
    glm::vec3 direccion;

    const glm::vec4 DIRECCION_INICIAL{1.0f, 0.0f, 0.0f, 0.0f};

private:
    sf::Vector2i ultimaPosicionRaton;
};


#endif //AST3ROIDS_NAVE3D_HPP
