#ifndef AST3ROIDS_OVNI3D_HPP
#define AST3ROIDS_OVNI3D_HPP


#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "../neural/include/neural/Network.h"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Disparo3D.hpp"

class Ovni3D : public Elemento3D {
public:
    Ovni3D(ControladorSonido *controladorSonido, float limitesMovimiento);

    virtual void actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Elemento3D &nave);
    void dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar = true,
                 sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    void cambiarEstado(EstadoOvni nuevoEstado);
    EstadoOvni getEstado(){ return estado; }

    virtual glm::vec3 direccionSegura(glm::vec3 posicion, std::vector<Asteroide3D> v);


    virtual int getPuntuacion() const;

    const float VELOCIDAD_INICIAL = 20.0f;
    glm::vec3 velocidad;
    glm::vec3 direccion;

protected:
    EstadoOvni estado;
    std::vector<Disparo3D> disparos;
    float limiteMovimiento;
    ControladorSonido *csonido;
    std::vector<glm::vec3> direcciones;
    ControladorSonido::Sonido sonidoOvni;
};


#endif //AST3ROIDS_OVNI3D_HPP
