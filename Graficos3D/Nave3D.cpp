#include <string>
#include <iostream>
#include <glm/gtx/quaternion.hpp>
#include "Nave3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

using namespace std;
using namespace sf;

Nave3D::Nave3D(ControladorSonido *controladorSonido, long int *punt, const float limitesMovimiento) :
        csonido(controladorSonido), Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                                               ControladorTexturas::getTextura(ControladorTexturas::NAVE)) {

    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::NAVE);
    velocidad = {0.0f, 0.0f, 0.0f};
    pos.posicion = {0.0f, 0.0f, 0.0f};
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = glm::angleAxis((float) -PI / 2, glm::vec3{0, 1, 0});
    dirFrente = glm::vec3(DIRECCION_FRENTE_INICIAL);
    puntuacion = punt;
    limiteMovimiento = limitesMovimiento;
}

void Nave3D::actualizar(std::vector<Asteroide3D> &asteroides, sf::Vector2i movRaton) {
    // Aplicar el movimiento del ratón a una rotación utilizando dos cuaternios.
    // X es el eje horizontal, alrededor del cual se inclina la nave (arriba-abajo).
    // Y es el eje vertical, alrededor del cual gira la nave (izquierda-derecha).
    glm::quat cuaternioInclinar = glm::angleAxis(-movRaton.y * 0.005f, dirDerecha);
    glm::quat cuaternioGirar = glm::angleAxis(-movRaton.x * 0.005f, dirArriba);
    pos.rotacion = glm::quat_cast(
            glm::toMat4(cuaternioGirar) * glm::toMat4(cuaternioInclinar) * glm::toMat4(pos.rotacion));

    glm::mat4 modelo = pos.matrizModelo();

    dirFrente = glm::vec3(modelo * DIRECCION_FRENTE_INICIAL);
    dirArriba = glm::vec3(modelo * DIRECCION_ARRIBA_INICIAL);
    dirDerecha = glm::vec3(modelo * DIRECCION_DERECHA_INICIAL);

    // Acelera
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        velocidad += dirFrente * ACELERACION;
        if (tamanoVector(velocidad) > VELOCIDAD_MAX) {
            velocidad = velocidad * 0.98f;
        }
        csonido->reproducir(ControladorSonido::ACELERAR);
    } else velocidad = velocidad * 0.98f;

    pos.posicion += velocidad * (1 / 60.f);

    if (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
        // Mover la nave al lugar opuesto en el que se encuentra.
        pos.posicion = glm::vec3{0, 0, 0} - pos.posicion;
    }

    //Se comprueba la colision con los asteroides
    for (int i = 0; i < asteroides.size(); i++) {
        if (colisionEsferaEsfera(pos.posicion, RADIO * pos.escala.z,
                                 asteroides[i].pos.posicion, Asteroide3D::RADIO * asteroides[i].pos.escala.y)) {
            //COLISION!!!!!!!!!!!!
            asteroides[i].colisionDetectada(asteroides);
            asteroides.erase(asteroides.begin() + i);
            i--;
            destruida();
        }
    }

    // Actualiza los disparos de la nave
    for (int i = 0; i < disparos.size(); i++) {
        disparos[i].actualizar();

        bool colisionado = false;

        //Se comprueba la colision de los disparos con los asteroides
        for (int j = 0; j < asteroides.size(); j++) {
            if (colisionPuntoEsfera(disparos[i].pos.posicion, asteroides[j].pos.posicion,
                                    1.0f * asteroides[j].pos.escala.y)) {
                //COLISION!!!!!!!!!!!!
                asteroides[j].colisionDetectada(asteroides);
                asteroides.erase(asteroides.begin() + j);
                j--;
                colisionado = true;
                break;
            }
        }
        if (colisionado || disparos[i].estado == DESTRUIDO) {
            disparos.erase(disparos.begin() + i);
            i--;
        }
    }
}

void Nave3D::dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states) const {
    // Dibuja los disparos
    for (const Disparo3D &disparo : disparos)
        disparo.dibujar(target, camara, states);

    predibujado(camara);
    draw(target, states);
}

void Nave3D::disparar() {
    disparos.emplace_back(dirFrente, pos.posicion, pos.rotacion, limiteMovimiento);
    csonido->reproducir(ControladorSonido::DISPARO, true);
}

void Nave3D::destruida() {
    vidas--;
}

int Nave3D::getVidas() {
    return vidas;
}
