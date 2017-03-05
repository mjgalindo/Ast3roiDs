#include <iostream>
#include "Asteroide.hpp"

Asteroide::Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, float size) {
    posicion = posicion_inicial;
    direccion = dir;
    velocidad = vel;
    this->size = size;
    version = tipo;
    // Definimos el asteroide como una serie de puntos conectados por orden
    poligono.setPrimitiveType(sf::LineStrip);
    switch (tipo) {
        case TIPO_0:
            poligono.resize(11);
            poligono[0].position = {-12.f, -5.7f};
            poligono[1].position = {-12.3f, -3.7f};
            poligono[2].position = {-4.7f, 8.5f};
            poligono[3].position = {4.3f, 8.7f};
            poligono[4].position = {13.f, 3.3f};
            poligono[5].position = {9.7f, -1.f};
            poligono[6].position = {9.5f, -8.3f};
            poligono[7].position = {6.3f, -13.5f};
            poligono[8].position = {0.5f, -7.7f};
            poligono[9].position = {-5.7f, -13.0f};
            poligono[10].position = {-12.f, -5.7f};
            break;
        case TIPO_1:
            poligono.resize(13);
            poligono[0].position = {-6.f, -11.2f};
            poligono[1].position = {-2.5f, -5.5f};
            poligono[2].position = {-11.5f, -5.5f};
            poligono[3].position = {-11.8f, 3.0f};
            poligono[4].position = {-3.8f, 12.0f};
            poligono[5].position = {4.0f, 8.8f};
            poligono[6].position = {6.8f, 12.5f};
            poligono[7].position = {12.2f, 5.5f};
            poligono[8].position = {5.2f, 1.f};
            poligono[9].position = {13.2f, -2.0f};
            poligono[10].position = {16.2f, -5.5f};
            poligono[11].position = {4.2f, -10.8f};
            poligono[12].position = {-6.f, -11.2f};
            break;
        case TIPO_2:
            poligono.resize(12);
            poligono[0].position = {-4.6f, -11.2f};
            poligono[1].position = {-11.0f, -5.4f};
            poligono[2].position = {-7.6f, -1.0f};
            poligono[3].position = {-10.8f, 5.8f};
            poligono[4].position = {-4.8f, 11.8f};
            poligono[5].position = {-1.0f, 8.0f};
            poligono[6].position = {6.7f, 10.3f};
            poligono[7].position = {12.7f, 2.6f};
            poligono[8].position = {7.4f, -2.7f};
            poligono[9].position = {12.2f, -5.7f};
            poligono[10].position = {7.0f, -11.0f};
            poligono[11].position = {-4.6f, -11.2f};
    }
}

//Getters
sf::VertexArray Asteroide::getPuntos() {
    return sf::VertexArray();
}

float Asteroide::getDireccion() {
    return direccion;
}

sf::Vector2f Asteroide::getPosicion() {
    return posicion;
}

sf::Vector2f Asteroide::getVelocidad() {
    return velocidad;
}

void Asteroide::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Transform t;
    // El orden en el que se efectuan las transformaciones es importante!
    t.rotate(direccion).translate(posicion).scale({size, size});
    target.draw(poligono, t);
    sf::CircleShape posicionC(10); posicionC.setPosition(posicion);
    target.draw(posicionC);
}

void Asteroide::mover(sf::Vector2u limites) {
    posicion += velocidad;
    if (posicion.x - 1 >= limites.x) {
        posicion.x -= limites.x;
    } else if (posicion.x + 1 <= 0.0) {
        posicion.x += limites.x;
    }
    if (posicion.y - 1 >= limites.y) {
        posicion.y -= limites.y;
    } else if (posicion.y + 1 <= 0.0) {
        posicion.y += limites.y;
    }
}
