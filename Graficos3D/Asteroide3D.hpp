#ifndef AST3ROIDS_ASTEROIDE3D_HPP
#define AST3ROIDS_ASTEROIDE3D_HPP

#include "Elemento3D.hpp"

class Asteroide3D : public Elemento3D {
public:
    Asteroide3D();
    Asteroide3D(glm::vec3 pos, glm::vec3 vel, glm::vec3 rot, glm::vec3 esc);

    void actualizar();
    void colisionDetectada(std::vector<Asteroide3D> &asteroides);

private:
    static constexpr float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
};


#endif //AST3ROIDS_ASTEROIDE3D_HPP
