#include <string>
#include <iostream>
#include "Nave3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

using namespace std;
using namespace sf;

Nave3D::Nave3D() :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::NAVE)) {

    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::NAVE);
    velocidad = {0.0f, 0.0f, 0.0f};
    pos.posicion = {0.0f, 0.0f, 0.0f};
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = {0.0f, -PI / 2, 0.0f};
    direccion = glm::vec3(DIRECCION_INICIAL);
    ultimaPosicionRaton = sf::Mouse::getPosition();
}

void Nave3D::actualizar() {
    // Gira la nave
    sf::Vector2i ratonActual = sf::Mouse::getPosition();
    sf::Vector2i desplazamientoRaton = ratonActual - ultimaPosicionRaton;
    ultimaPosicionRaton = ratonActual;

    // Aplicar el movimiento del ratón a una rotación.
    // X es el eje horizontal, alrededor del cual se inclina la nave (arriba-abajo).
    // Y es el eje vertical, alrededor del cual gira la nave (izquierda-derecha).
    glm::vec4 rotacion = {0.0f, -desplazamientoRaton.x * 0.005f, -desplazamientoRaton.y * 0.005f, 0.0f};

    // DEBUG:
    //rotacion = {0.0f, -3 * 0.005f, -1 * 0.005f, 0.0f};

    // Transformar la rotación al espacio local de la nave y aplicarla (actualizando pos.rotacion).
    // TODO: Implementarlo bien!
    pos.rotacion = pos.rotacion + glm::vec3(matrizRotacion(pos.rotacion) * rotacion);
    normalizaRotacion(pos.rotacion);

    direccion = matrizRotacion(pos.rotacion) * DIRECCION_INICIAL;
    direccion = glm::normalize(direccion);

    // Acelera
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        velocidad += direccion * 0.1f;
    else velocidad = velocidad * 0.98f;

    pos.posicion += velocidad * (1 / 60.f);

    // Actualiza los disparos de la nave
    for (Disparo3D& disparo : disparos)
        disparo.actualizar();
}

void Nave3D::dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states) const {
    // Dibuja los disparos
    for (const Disparo3D& disparo : disparos)
        disparo.dibujar(target, camara, states);

    predibujado(camara);
    draw(target, states);
}

void Nave3D::disparar() {
    disparos.emplace_back(direccion, pos.posicion);
    std::cout << "PEW!! ";
}