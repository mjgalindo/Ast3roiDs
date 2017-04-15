#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Elemento3D.hpp"

class Nave3D : public Elemento3D {
public:
    Nave3D(vj::Shader *shader);

    void actualizar();

    void posiciones(glm::vec3 &posicion, glm::vec3 &rotacion);

private:

    const float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
    glm::vec4 direccion = {1.0f, 0.0f, 0.0f, 0.0f};
};


#endif //AST3ROIDS_NAVE3D_HPP
