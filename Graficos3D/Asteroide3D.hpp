#ifndef AST3ROIDS_ASTEROIDE3D_HPP
#define AST3ROIDS_ASTEROIDE3D_HPP

#include "Elemento3D.hpp"
#include "../Estados.hpp"
#include "../ControladorSonido.hpp"
#include "../Estados.hpp"

class Asteroide3D : public Elemento3D {
public:
    Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento);

    Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento,
                glm::vec3 posicion, glm::vec3 vel, glm::vec3 rot, Tipo3D tipo, Tamano3D tam3D);

    void actualizar();

    void colisionDetectada(std::vector<Asteroide3D> &asteroides);

    static constexpr float RADIO = 1.0f;

private:
    static constexpr float VELOCIDAD_MAX = 0.2f;

    Tipo3D version;
    Tamano3D tamano3D;

    glm::vec3 velocidad;
    glm::quat velocidadAngular;
    ControladorSonido *csonido;

    float limiteMovimiento;
};


#endif //AST3ROIDS_ASTEROIDE3D_HPP
