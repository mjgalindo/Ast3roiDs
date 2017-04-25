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
    cooldown = clock();
}

void Nave3D::actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Ovni3D &ovni, sf::Vector2i movRaton) {
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
    }

    //Se comprueba la colision con los asteroides
    for (int i = 0; i < asteroides.size(); i++) {
        if (asteroides[i].estado != NORMAL && colisionEsferaEsfera(pos.posicion, RADIO * pos.escala.z,
                                                                   asteroides[i].pos.posicion,
                                                                   Asteroide3D::RADIO * asteroides[i].pos.escala.y)) {
            // Se destruyen tanto el asteroide como la nave.
            asteroides[i].colisionDetectada(nivel, asteroides);
            destruir();
            break;
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
                asteroides[j].colisionDetectada(nivel, asteroides);
                colisionado = true;
                break;
            }
        }

        //Se comprueba la colision de los disparos con el ovni
        if(!colisionado && colisionPuntoEsfera(disparos[i].pos.posicion, ovni.pos.posicion, 4.9f*ovni.pos.escala.y)){
            colisionado = true;
        }

        if (colisionado || disparos[i].estado == DESTRUIDO) {
            disparos.erase(disparos.begin() + i);
            i--;
        }
    }
}

void Nave3D::dibujar(sf::RenderTarget &target, Camara &camara, bool malla, sf::RenderStates states) const {
    // Dibuja los disparos
    for (const Disparo3D &disparo : disparos)
        disparo.dibujar(target, camara, states);

    predibujado(camara);
    if (malla) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    draw(target, states);
    if (malla) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Nave3D::disparar() {
    if(disparos.size()<4) {
        disparos.emplace_back(dirFrente, pos.posicion, pos.rotacion, limiteMovimiento);
        csonido->reproducir(ControladorSonido::DISPARO, true);
    }
}

void Nave3D::destruir() {
    pos.posicion = {0, 0, 0};
    vidas--;
}

int Nave3D::getVidas() {
    return vidas;
}

void Nave3D::hiperespacio(float radio){
    double tiempo = (clock() - cooldown) / (double) CLOCKS_PER_SEC;
    if (tiempo > 2) {
        cooldown = clock();
        float x = valorAleatorio(0, radio);
        float y = valorAleatorio(0, radio);
        float z = valorAleatorio(0, radio);
        while(pow(x,2)+pow(y,2)+pow(z,2)>=pow(radio,2)){
            valorAleatorio(0, radio);
            valorAleatorio(0, radio);
            valorAleatorio(0, radio);
        }

        pos.posicion = {x,y,z};

        if (valorAleatorio() < 0.4) {
            destruir();
        }

    }
}
