//
// Created by Jorge on 21/02/2017.
//

#include "Disparo.hpp"

Disparo::Disparo(float origenX, float origenY, float direccionN) {
    posicionInicial = sf::Vector2f(origenX, origenY);
    direccion = direccionN;
    posicion = posicionInicial;
}

void Disparo::movimiento() {

}

float Disparo::distanciaRecorrida() {
    sf::Vector2f distancia = posicion - posicionInicial;
    return sqrtf(distancia.x*distancia.x + distancia.y*distancia.y);
}

void Disparo::desaparecer() {

}