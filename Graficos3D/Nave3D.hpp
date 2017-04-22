#ifndef AST3ROIDS_NAVE3D_HPP
#define AST3ROIDS_NAVE3D_HPP

#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Disparo3D.hpp"

class Nave3D : public Elemento3D {
public:
    Nave3D();

    void actualizar(std::vector<Asteroide3D> &asteroides);
    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    const float VELOCIDAD_MAX = 0.5f;

    glm::vec3 velocidad;
    glm::vec3 direccion;

    const glm::vec4 DIRECCION_INICIAL{1.0f, 0.0f, 0.0f, 0.0f};

private:
    sf::Vector2i ultimaPosicionRaton;
    std::vector<Disparo3D> disparos;

};


#endif //AST3ROIDS_NAVE3D_HPP
