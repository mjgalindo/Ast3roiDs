#include <string>
#include <iostream>
#include "Ovni3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

using namespace std;
using namespace sf;

Ovni3D::Ovni3D(ControladorSonido *controladorSonido, float limitesMovimiento) :
        csonido(controladorSonido),
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::OVNI)) {

    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::OVNI);
    pos.escala = {7.0f, 7.0f, 7.0f};
    pos.rotacion = glm::angleAxis((float) -PI / 2, glm::vec3{0.0f, 1.0f, 0.0f});
    limiteMovimiento = limitesMovimiento;
    estado = MUERTO;
}

void Ovni3D::actualizar(std::vector<Asteroide3D> asteroides, Nave3D nave) {
    if(estado == VIVO) {
        pos.posicion += velocidad * (1 / 60.f);
        if (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
            pos.posicion = glm::vec3{0, 0, 0} - pos.posicion;
            while (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
                pos.posicion.x = (abs(pos.posicion.x) - 0.1f) * pos.posicion.x / abs(pos.posicion.x);
                pos.posicion.y = (abs(pos.posicion.y) - 0.1f) * pos.posicion.y / abs(pos.posicion.y);
                pos.posicion.z = (abs(pos.posicion.z) - 0.1f) * pos.posicion.z / abs(pos.posicion.z);
            }
        }
        //Se comprueba la colision con los asteroides
        for (int i = 0; i < asteroides.size(); i++) {
            if (colisionEsferaEsfera(this->pos.posicion, 7.6f * this->pos.escala.z, asteroides[i].pos.posicion,
                                     1.0f * asteroides[i].pos.escala.y)) {
                //COLISION!!!!!!!!!!!!
                asteroides[i].colisionDetectada(asteroides);
                asteroides.erase(asteroides.begin() + i);
                i--;
                cambiarEstado(MUERTO);
            }
        }

        if (valorAleatorio() <= 0.01) {
            disparar();
        }

        if (valorAleatorio() <= 0.001) {
            direccion = glm::vec3(valorAleatorio(-1.0f, 1.0f), valorAleatorio(-1.0f, 1.0f),
                                  valorAleatorio(-1.0f, 1.0f));
            velocidad = VELOCIDAD_INICIAL * direccion;
        }

        //Se comprueba la colision del ovni con la nave
        if (colisionEsferaEsfera(pos.posicion, 1.0f, nave.pos.posicion, 7.6f * nave.pos.escala.z)) {
            //COLISION
            nave.destruida();
            cambiarEstado(MUERTO);
        }
    } else if(estado == MUERTO) {
        if(valorAleatorio() <= 0.005) {
            cambiarEstado(VIVO);
        }
    }
    bool colisionado = false;
    // Actualiza los disparos del ovni
    for (int i = 0; i < disparos.size(); i++) {
        disparos[i].actualizar();

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
        //Se comprueba la colision de los disparos con la nave
        if (!colisionado &&
            colisionPuntoEsfera(disparos[i].pos.posicion, nave.pos.posicion, 7.6f * nave.pos.escala.z)) {
            //COLISION!!!!!!!!!!!!
            nave.destruida();
        }

        if (colisionado || disparos[i].estado == DESTRUIDO) {
            disparos.erase(disparos.begin() + i);
            i--;
        }

    }

}

void Ovni3D::dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states) const {
    if(estado == VIVO) {
        predibujado(camara);
        draw(target, states);
    }
    // Dibuja los disparos
    for (const Disparo3D &disparo : disparos)
        disparo.dibujar(target, camara, states);
}

void Ovni3D::disparar() {
    disparos.emplace_back(direccion, pos.posicion, pos.rotacion, limiteMovimiento);

    csonido->reproducir(ControladorSonido::DISPARO,true);
}

void Ovni3D::cambiarEstado(EstadoOvni nuevoEstado) {
    estado = nuevoEstado;
    if(estado == VIVO) {
        pos.posicion = {valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f)};
        direccion = glm::vec3(valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f));
        velocidad = VELOCIDAD_INICIAL*direccion;
        csonido->reproducir(ControladorSonido::OVNI_GRANDE,false);
    } else if(estado == MUERTO) {
        csonido->detener(ControladorSonido::OVNI_GRANDE);
    }
}