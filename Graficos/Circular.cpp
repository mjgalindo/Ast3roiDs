#include "Circular.hpp"

//Constructores
Circular::Circular() {}

Circular::Circular(sf::Vector2f p, float r){
    posicion = p;
    radio = r;
}

//Destructor
Circular::~Circular() {}

//Setters
void Circular::setPosicion(sf::Vector2f p){
    posicion = p;
}

void Circular::setRadio(float r){
    radio = r;
}

//Getters
sf::Vector2f Circular::getPosicion(){
    return posicion;
}

int Circular::getEstado(){
    return estado;
}

float Circular::getRadio(){
    return radio;
}