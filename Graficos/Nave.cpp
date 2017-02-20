#include "Nave.hpp"

//Constructores
Nave::Nave() : Movil() {}

Nave::Nave(Vector2f posicion, Vector2f vel, float velAng=1.0, int v=3, long int p=0, Estado e=OK)
        : Movil(posicion, vel) {
    velocidadAngular = velAng;
    vidas = v;
    puntuacion = p;

    estado = e;
}

Nave::Nave(Vector2f posicion, Vector2f vel, sf::Texture t, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK)
        : Movil(posicion, vel, t) {
    velocidadAngular = velAng;
    vidas = v;
    puntuacion = p;

    estado = e;
}

Nave::Nave(float posX, float posY, float velX, float velY, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK)
        : Movil(posX, posY, velX, velY) {
    velocidadAngular = velAng;
    vidas = v;
    puntuacion = p;

    estado = e;
}

Nave::Nave(float posX, float posY, float velX, float velY, sf::Texture t, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK)
        :Movil(posX, posY, velX, velY, t) {
    velocidadAngular = velAng;
    vidas = v;
    puntuacion = p;

    estado = e;
}

//Destructor
Nave::~Nave() : ~Movil() {}

//Getters
float Nave::getVelocidadAngular() {
    return velocidadAngular;
}

int Nave::getVidas() {
    return vidas;
}

long int Nave::getPuntuacion() {
    return puntuacion;
}

Estado Nave::getEstado() {
    return estado;
}

const sf::Texture* Nave::getTxtAcelerando() {
    return naveAcelerando;
}

const sf::Texture* Nave::getTxtDestruida() {
    return naveDestruida;
}
const sf::Texture* Nave::getTxtReconstruyendo() {
    return naveReconstruyendo;
}

//Setters
void Nave::setVelocidadAngular(float va) {
    velocidadAngular = va;
}

void Nave::setVidas(int v) {
    vidas = v;
}

void Nave::setPuntuacion(long int punt) {
    puntuacion = punt;
}

void Nave::setEstado(Estado est) {
    estado = est;
}

void Nave::setTxtAcelerando(sf::Texture t) {
    naveAcelerando = t;
}

void Nave::setTxtDestruida(sf::Texture t) {
    naveDestruida = t;
}

void Nave::setTxtReconstruyendo(sf::Texture t) {
    naveReconstruyendo = t;
}

//Otros
void Nave::destruir() {
    vidas--;
    estado = DESTRUIDA;
}

void Nave::reconstruir() {
    estado = RECONSTRUYENDO;
}

void Nave::aumentarPuntuacion(int puntos) {
    puntuacion += puntos;
}

void Nave::disparar() {
    // PIUM
}

void Nave::girar() {
    rotate(velocidadAngular);
}

void Nave::saltar() {
    // setPosition(rand(0,MAX_X), rand(0,MAX_Y));
}