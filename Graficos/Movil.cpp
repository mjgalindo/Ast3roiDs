#include "Movil.hpp"

//Constructores
Movil::Movil() : sf::Sprite() {}

Movil::Movil(Vector2f posicion, Vector2f vel) : sf::Sprite() {
    setPosition(posicion);
    velocidad = vel;
}

Movil::Movil(Vector2f posicion, Vector2f vel, sf::Texture textura) : sf::Sprite(textura) {
    setPosition(posicion);
    velocidad = vel;
}

Movil::Movil(float posX, float posY, float velX, float velY) : sf::Sprite() {
    setPosition(posX, posY);
    velocidad = Vector2f(velX, velY);
}

Movil::Movil(float posX, float posY, float velX, float velY, sf::Texture textura) : sf::Sprite(textura) {
    setPosition(posX, posY);
    velocidad = Vector2f(velX, velY);
}

//Destructor
Movil::~Movil() : sf::~Sprite() {}

//Getters
Vector2f Movil::getVelocidad() {
    return velocidad;
}

//Setters
void Movil::setVelocidad(Vector2f vel) {
    velocidad = vel;
}

void Movil::setVelocidad(float velX, float velY) {
    velocidad = Vector2f(velX, velY);
}

//Otros
void acelerar(Vector2f a) {
    velocidad += a;
}

void acelerar(float ax, float ay) {
    velocidad.x += velX;
    velocidad.y += velY;
}

void mover(){
    move(velocidad);
}