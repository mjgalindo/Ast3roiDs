#include "Triangular.hpp"

//Constructores
Triangular::Triangular() {}

Triangular::Triangular(sf::Vector2f p, float d, float t) {
    posicion = p;
    direccion = d;
    tamano = t;
}

//Destructor
Triangular::~Triangular() {}

//Setters
void Triangular::setPosicion(sf::Vector2f p) {
    posicion = p;
}

void Triangular::setDireccion(float d) {
    direccion = d;
}

void Triangular::setTamano(float t) {
    tamano = t;
}

void Triangular::setVertices(sf::VertexArray v) {
    vs = v;
}

//Getters
sf::Vector2f Triangular::getPosicion() {
    return posicion;
}

float Triangular::getDireccion() {
    return direccion;
}

float Triangular::getTamano() {
    return tamano;
}

int Triangular::getEstado() {
    return estado;
}

sf::VertexArray Triangular::getVertices() {
    return vs;
}

sf::VertexArray Triangular::getTriangulo() {
    sf::Transform t;
    t.rotate(direccion * (180.0 / 3.14), posicion).translate(posicion).scale({tamano, tamano});

    sf::VertexArray triangulo;
    triangulo.resize(vs.getVertexCount());
    for (int i = 0; i < vs.getVertexCount(); i++) {
        triangulo[i].position = t.transformPoint(vs[i].position);
    }

    return triangulo;
}