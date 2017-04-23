#ifndef AST3ROIDS_DISPARO3D_HPP
#define AST3ROIDS_DISPARO3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "Elemento3D.hpp"

class Disparo3D : public Elemento3D {
public:
    Disparo3D(glm::vec3 direccion, glm::vec3 posicion, glm::quat rotacion, float limitesMovimiento);

    void actualizar();

    static constexpr float VELOCIDAD_BASE = 3.0f;
    static constexpr float DISTANCIA_MAX = 230.0f;

    glm::vec3 velocidad;
    glm::vec3 posicionInicial;
    float distanciaRestante;
    float limiteMovimiento;
};


#endif //AST3ROIDS_DISPARO3D_HPP
