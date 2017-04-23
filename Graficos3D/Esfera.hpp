#ifndef AST3ROIDS_ESFERA_HPP
#define AST3ROIDS_ESFERA_HPP

#include "Elemento3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"

class Esfera : public Elemento3D {
public:
    Esfera(ControladorTexturas::TipoTextura textura, glm::vec3 posicion = glm::vec3{0, 0, 0},
           glm::vec3 escala = glm::vec3{1, 1, 1}, bool verSoloMalla = false);

    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    bool modoMalla = false;

};

#endif //AST3ROIDS_ESFERA_HPP
