//
// Created by Jorge on 21/02/2017.
//

#ifndef AST3ROIDS_DISPARO_HPP
#define AST3ROIDS_DISPARO_HPP

#include <SFML/Graphics.hpp>
#include <Math.h>
class Disparo {

private:
    sf::Vector2f posicion;
    sf::Vector2f posicionInicial;
    float direccion;
    const float velocidad = 10.0;
    const float distanciaMax = 100.0;
    sf::Clock reloj;

public:
    Disparo(float, float, float);
    void movimiento();
    float distanciaRecorrida();
    void desaparecer();
};

#endif //AST3ROIDS_DISPARO_HPP
