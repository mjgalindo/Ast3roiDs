#ifndef AST3ROIDS_ASTEROIDE3D_HPP
#define AST3ROIDS_ASTEROIDE3D_HPP

#include "Elemento3D.hpp"
#include "../ControladorSonido.hpp"
#include "../Estados.hpp"

class Asteroide3D : public Elemento3D {
public:
    Asteroide3D(ControladorSonido *controladorSonido);

    Asteroide3D(ControladorSonido *controladorSonido, glm::vec3 pos, glm::vec3 vel, glm::vec3 rot, Tipo3D tipo,
                Tamano3D tam3D);

    void actualizar();

    void colisionDetectada(std::vector<Asteroide3D> &asteroides);

private:
    static constexpr float VELOCIDAD_MAX = 0.5f;

    Tipo3D version;
    Tamano3D tamano3D;

    glm::vec3 velocidad;
    ControladorSonido *csonido;
};


#endif //AST3ROIDS_ASTEROIDE3D_HPP
