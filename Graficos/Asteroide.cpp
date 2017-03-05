#include <iostream>
#include "Asteroide.hpp"

Asteroide::Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, Tamano tam) {
    posicion = posicion_inicial;
    direccion = dir;
    velocidad = vel;
    tamano = tam;
    version = tipo;
    // Definimos el asteroide como una serie de puntos conectados por orden
    poligono.setPrimitiveType(sf::LineStrip);
    switch (version) {
        case TIPO_0:
            poligono.resize(11);
            poligono[0].position = {-0.888889f, -0.422222f};
            poligono[1].position = {-0.911111f, -0.274074f};
            poligono[2].position = {-0.348148f, 0.62963f};
            poligono[3].position = {0.318519f, 0.644444f};
            poligono[4].position = {0.962963f, 0.244444f};
            poligono[5].position = {0.718519f, -0.0740741f};
            poligono[6].position = {0.703704f, -0.614815f};
            poligono[7].position = {0.466667f, -1.f};
            poligono[8].position = {0.037037f, -0.57037f};
            poligono[9].position = {-0.422222f, -0.962963f};
            poligono[10].position = {-0.888889f, -0.422222f};
            break;
        case TIPO_1:
            poligono.resize(13);
            poligono[0].position = {-0.37037f, -0.691358f};
            poligono[1].position = {-0.154321f, -0.339506f};
            poligono[2].position = {-0.709877f, -0.339506f};
            poligono[3].position = {-0.728395f, 0.185185f};
            poligono[4].position = {-0.234568f, 0.740741f};
            poligono[5].position = {0.246914f, 0.54321f};
            poligono[6].position = {0.419753f, 0.771605f};
            poligono[7].position = {0.753086f, 0.339506f};
            poligono[8].position = {0.320988f, 0.0617284f};
            poligono[9].position = {0.814815f, -0.123457f};
            poligono[10].position = {1.f, -0.339506f};
            poligono[11].position = {0.259259f, -0.666667f};
            poligono[12].position = {-0.37037f, -0.691358f};
            break;
        case TIPO_2:
            poligono.resize(12);
            poligono[0].position = {-0.362205f, -0.88189f};
            poligono[1].position = {-0.866142f, -0.425197f};
            poligono[2].position = {-0.598425f, -0.0787402f};
            poligono[3].position = {-0.850394f, 0.456693f};
            poligono[4].position = {-0.377953f, 0.929134f};
            poligono[5].position = {-0.0787402f, 0.629921f};
            poligono[6].position = {0.527559f, 0.811024f};
            poligono[7].position = {1.f, 0.204724f};
            poligono[8].position = {0.582677f, -0.212598f};
            poligono[9].position = {0.96063f, -0.448819f};
            poligono[10].position = {0.551181f, -0.866142f};
            poligono[11].position = {-0.362205f, -0.88189f};
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

float Asteroide::getRadio() {
    return tamano;
}

int Asteroide::getPuntuacion() {
    switch(tamano){
        case TAM_0:
            return 100;
        case TAM_1:
            return 50;
        case TAM_2:
            return 20;
        default:
            return 0;
    }
}

void Asteroide::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Transform t;
    // El orden en el que se efectuan las transformaciones es importante!
    t.rotate(direccion).translate(posicion).scale({(float)tamano, (float)tamano});
    target.draw(poligono, t);
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
