#ifndef AST3ROIDS_OVNI3D_HPP
#define AST3ROIDS_OVNI3D_HPP


#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Disparo3D.hpp"

class Ovni3D : public Elemento3D {
public:
    Ovni3D();

    void actualizar(std::vector<Asteroide3D> asteroides);
    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    glm::vec3 velocidad;
    glm::vec3 direccion;

private:
    std::vector<Disparo3D> disparos;

};


#endif //AST3ROIDS_OVNI3D_HPP
