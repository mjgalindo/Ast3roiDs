#ifndef AST3ROIDS_OVNI3D_HPP
#define AST3ROIDS_OVNI3D_HPP


#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Disparo3D.hpp"

class Ovni3D : public Elemento3D {
public:
    Ovni3D(ControladorSonido *controladorSonido, float limitesMovimiento);

    void actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Elemento3D &nave);
    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    void cambiarEstado(EstadoOvni nuevoEstado);

    glm::vec3 direccionSegura(glm::vec3 posicion, std::vector<Asteroide3D> v);

    const float VELOCIDAD_INICIAL = 5.0f;
    glm::vec3 velocidad;
    glm::vec3 direccion;

private:
    EstadoOvni estado;
    std::vector<Disparo3D> disparos;
    float limiteMovimiento;
    ControladorSonido *csonido;
    glm::vec3 ultimaDireccion;
    std::vector<glm::vec3> direcciones;

};


#endif //AST3ROIDS_OVNI3D_HPP
