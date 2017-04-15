#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Elemento3D.hpp"

class Nave3D : public Elemento3D {
public:
    Nave3D(vj::Shader* shader);

    void mover();

    glm::vec3 rotacion() {
        return pos.rotacion;
    }
    void setRot(glm::vec3 rot)
    {
        pos.rotacion = rot;
    }

private:

    const float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
};


#endif //AST3ROIDS_NAVE3D_HPP
