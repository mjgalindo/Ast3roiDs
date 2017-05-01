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
    estado = INVULNERABLE;
}

void Nave3D::actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Ovni3D &ovni, sf::Vector2i movRaton) {
    if (estado == INVULNERABLE & reloj.getElapsedTime().asSeconds() > TIEMPO_INVULNERABILIDAD) estado = NORMAL;
    // Aplicar el movimiento del ratón a una rotación utilizando dos cuaternios.
    // X es el eje horizontal, alrededor del cual se inclina la nave (arriba-abajo).
    // Y es el eje vertical, alrededor del cual gira la nave (izquierda-derecha).
    glm::quat cuaternioInclinar = glm::angleAxis(-movRaton.y * 0.005f, dirDerecha);
    glm::quat cuaternioGirar = glm::angleAxis(-movRaton.x * 0.005f, dirArriba);
    pos.rotacion = glm::normalize(glm::quat_cast(
            glm::toMat4(cuaternioGirar) * glm::toMat4(cuaternioInclinar) * glm::toMat4(pos.rotacion)));
    glm::mat4 modelo = pos.matrizModelo();

    dirFrente = glm::vec3(modelo * DIRECCION_FRENTE_INICIAL);
    dirArriba = glm::vec3(modelo * DIRECCION_ARRIBA_INICIAL);
    dirDerecha = glm::vec3(modelo * DIRECCION_DERECHA_INICIAL);

    // Acelera
    if (sf::Keyboard::isKeyPressed(teclaAcelerar)) {
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
        csonido->reproducir(ControladorSonido::TELETRANSPORTE);
    }

    //Se comprueba la colision con los asteroides y el ovni si la nave no es invulnerable
    if (estado != INVULNERABLE){
        for (int i = 0; i < asteroides.size(); i++) {
            if (asteroides[i].estado == NORMAL && colisionEsferaEsfera(pos.posicion, RADIO * pos.escala.z,
                                                                       asteroides[i].pos.posicion,
                                                                       Asteroide3D::RADIO * asteroides[i].pos.escala.y)) {
                // Se destruyen tanto el asteroide como la nave.
                asteroides[i].colisionDetectada(nivel, asteroides);
                switch(asteroides[i].getTamano3D()){
                    case TAM3D_0:
                        *puntuacion += 20;
                        break;
                    case TAM3D_1:
                        *puntuacion += 50;
                        break;
                    case TAM3D_2:
                        *puntuacion += 100;
                        break;
                    default:
                        break;
                }
                destruir();
                break;
            }
        }

        if (estado == NORMAL && colisionEsferaEsfera(ovni.pos.posicion, 4.8f * ovni.pos.escala.y , pos.posicion, 7.6f * pos.escala.z)) {
            //COLISION
            *puntuacion += 1000;
            destruir();
            ovni.cambiarEstado(MUERTO);
        }
    }

    // Actualiza los disparos de la nave
    for (int i = 0; i < disparos.size(); i++) {
        disparos[i].actualizar();
        // Si el disparo ha alcanzado el final de su trayectoria se borra y
        // se continua con el siguiente
        if (disparos[i].estado == DESTRUIDO){
            disparos.erase(disparos.begin() + i);
            i--;
            continue;
        }

        //Se comprueba la colision de los disparos con los asteroides
        for (int j = 0; j < asteroides.size(); j++) {
            if (asteroides[j].estado == NORMAL &&
                    colisionPuntoEsfera(disparos[i].pos.posicion,
                                        asteroides[j].pos.posicion, 1.0f * asteroides[j].pos.escala.y)) {
                // Colision disparo-asteroide
                asteroides[j].colisionDetectada(nivel, asteroides);
                switch(asteroides[j].getTamano3D()){
                    case TAM3D_0:
                        *puntuacion += 20;
                        break;
                    case TAM3D_1:
                        *puntuacion += 50;
                        break;
                    case TAM3D_2:
                        *puntuacion += 100;
                        break;
                    default:
                        break;
                }
                disparos[i].estado = DESTRUIDO;
                break;
            }
        }

        //Se comprueba la colision de los disparos con el ovni
        if(disparos[i].estado != DESTRUIDO && ovni.getEstado()==VIVO && colisionPuntoEsfera(disparos[i].pos.posicion, ovni.pos.posicion, 7.6f*ovni.pos.escala.z)){
            disparos[i].estado = DESTRUIDO;
            *puntuacion += 1000;
            ovni.cambiarEstado(EstadoOvni::MUERTO);
        }

        if (disparos[i].estado == DESTRUIDO) {
            disparos.erase(disparos.begin() + i);
            i--;
        }
    }
}

void Nave3D::dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar, sf::RenderStates states) const {
    // Dibuja los disparos
    for (const Disparo3D &disparo : disparos)
        disparo.dibujar(target, camara, rellenar, states);
    Elemento3D::dibujar(target, camara, rellenar && estado != INVULNERABLE, states);
}

void Nave3D::disparar() {
    if(disparos.size()<4) {
        disparos.emplace_back(dirFrente, pos.posicion, pos.rotacion, limiteMovimiento);
        csonido->reproducir(ControladorSonido::DISPARO, true);
    }
}

void Nave3D::destruir() {
    csonido->reproducir(ControladorSonido::HAS_MUERTO);
    estado = INVULNERABLE;
    reloj.restart();
    pos.posicion = {0, 0, 0};
    disparos.clear();
    vidas--;
}

int Nave3D::getVidas() {
    return vidas;
}

void Nave3D::hiperespacio() {
    if (relojCooldown.getElapsedTime().asSeconds() > 2) {
        relojCooldown.restart();
        pos.posicion = glm::normalize(glm::vec3{
                valorAleatorio(-1, 1),
                valorAleatorio(-1, 1),
                valorAleatorio(-1, 1),
        }) * valorAleatorio(-limiteMovimiento, limiteMovimiento);

        if (valorAleatorio() < 0.4) {
            destruir();
        }

    }
}
