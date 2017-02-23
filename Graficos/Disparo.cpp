//
// Created by Jorge on 21/02/2017.
//

#include "Disparo.hpp"

Disparo::Disparo() {}

Disparo::Disparo(float origenX, float origenY, float direccionN) {
    posicionInicial = sf::Vector2f(origenX, origenY);
    direccion = direccionN;
    posicion = posicionInicial;
    velocidad = sf::Vector2f(cos(direccion), sin(direccion));
    distanciaMax = 500.0;
    distanciaRecorrida = 0.0;
}

void Disparo::mover(sf::Vector2u limites) {
    posicion.x += velocidad.x;
    if(posicion.x-1 >= limites.x) {
        posicion.x -= limites.x;
    } else if(posicion.x+1 <= 0.0) {
        posicion.x += limites.x;
    }

    posicion.y += velocidad.y;
    if(posicion.y-1 >= limites.y) {
        posicion.y -= limites.y;
    } else if(posicion.y+1 <= 0.0) {
        posicion.y += limites.y;
    }
    distanciaRecorrida += sqrtf(pow(velocidad.x,2) + pow(velocidad.y,2));
}

bool Disparo::terminado() {
    return distanciaRecorrida >= distanciaMax;
}


void Disparo::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    sf::CircleShape disparo(3.0);
    disparo.setFillColor(sf::Color::White);
    disparo.setPosition(posicion.x,posicion.y);

    target.draw(disparo);
}