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
    pos.escala = {1.0f, 1.0f, 1.0f};
    pos.rotacion = glm::angleAxis((float) -PI / 2, glm::vec3{0.0f, 1.0f, 0.0f});
    limiteMovimiento = limitesMovimiento;
    estado = MUERTO;
    direcciones = {glm::vec3(1.0f,1.0f,1.0f),
                   glm::vec3(1.0f,0.0f,1.0f),glm::vec3(0.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,0.0f),
                   glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f),glm::vec3(0.0f,0.0f,1.0f),
                   glm::vec3(-1.0f,-1.0f,-1.0f),
                   glm::vec3(-1.0f,0.0f,-1.0f),glm::vec3(0.0f,-1.0f,-1.0f),glm::vec3(-1.0f,-1.0f,0.0f),
                   glm::vec3(-1.0f,0.0f,0.0f),glm::vec3(0.0f,-1.0f,0.0f),glm::vec3(0.0f,0.0f,-1.0f),
                   glm::vec3(1.0f,-1.0f,1.0f),glm::vec3(-1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,-1.0f),
                   glm::vec3(1.0f,-1.0f,-1.0f),glm::vec3(-1.0f,1.0f,-1.0f),glm::vec3(-1.0f,-1.0f,1.0f)};
}

void Ovni3D::actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Elemento3D &nave) {
    if(estado == VIVO) {
        direccion = direccionSegura(pos.posicion,asteroides);
        velocidad = direccion * VELOCIDAD_INICIAL;
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
            if (asteroides.at(i).estado == NORMAL && colisionEsferaEsfera(pos.posicion, 7.6f * pos.escala.z, asteroides.at(i).pos.posicion,
                                     Asteroide3D::RADIO * asteroides.at(i).pos.escala.y)) {
                //COLISION!!!!!!!!!!!!
                asteroides.at(i).colisionDetectada(nivel, asteroides);
                asteroides.erase(asteroides.begin() + i);
                i--;
                cambiarEstado(MUERTO);
            }
        }

        if (valorAleatorio() <= 0.01 && estado == VIVO) {
            disparar();
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
                asteroides[j].colisionDetectada(nivel,asteroides);
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
            nave.destruir();
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
        pos.posicion = {
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
        };
        direccion = direcciones.at(enteroAleatorio(0,direcciones.size()-1));
        velocidad = VELOCIDAD_INICIAL*direccion;
        csonido->reproducir(ControladorSonido::OVNI_GRANDE,false);
    } else if(estado == MUERTO) {
        csonido->detener(ControladorSonido::OVNI_GRANDE);
    }
}

glm::vec3 Ovni3D::direccionSegura(glm::vec3 posicion, std::vector<Asteroide3D> v) {
    float vMax = VELOCIDAD_INICIAL;
    float radioPeligro = 20.0f;
    vector<glm::vec3> direccionesSeguras;
    vector<glm::vec3> posiciones;
    for (int i = 0; i < v.size(); i++) {
        posiciones.push_back(v.at(i).pos.posicion);
    }
    glm::vec3 posicionAux, velocidadAux;
    for (unsigned long long i = 0; i < direcciones.size(); i++) {
        posicionAux = posicion;
        velocidadAux = direcciones.at(i)*vMax;
        bool choque = false;
        float distanciaRecorrida = 0.0f;
        while (distanciaRecorrida < radioPeligro && !choque) {
            //MOVER OVNI Y COMPROBAR QUE CHOCA
            posicionAux = posicionAux + velocidadAux * (1 / 60.f);
            // Evita los limites del espacio
            if (distanciaEuclidea(posicionAux, glm::vec3{0, 0, 0}) > limiteMovimiento) {
                posicionAux = glm::vec3{0, 0, 0} - posicionAux;
                while (distanciaEuclidea(posicionAux, glm::vec3{0, 0, 0}) > limiteMovimiento) {
                    posicionAux.x = (abs(posicionAux.x) - 0.1f) * posicionAux.x / abs(posicionAux.x);
                    posicionAux.y = (abs(posicionAux.y) - 0.1f) * posicionAux.y / abs(posicionAux.y);
                    posicionAux.z = (abs(posicionAux.z) - 0.1f) * posicionAux.z / abs(posicionAux.z);
                }
            }
            for (int j = 0; j < v.size(); j++) {
                v.at(j).actualizar();
                if ((v.at(j).estado == NORMAL && colisionEsferaEsfera(posicionAux, 7.6f * pos.escala.z, v.at(j).pos.posicion,
                                                                               Asteroide3D::RADIO * v.at(j).pos.escala.y))) {
                    choque = true;
                    break;
                }
            }
            distanciaRecorrida += vMax/60.0f;
        }
        if (!choque) {
            if (direcciones.at(i) == direccion) {
                return direccion;
            }
            direccionesSeguras.push_back((direcciones.at(i)));
        }
        for (int j = 0; j < posiciones.size(); j++) {
            v.at(j).pos.posicion=posiciones.at(j);
        }
    }
    if (direccionesSeguras.size() == 0) {
        return direccion;
    }
    int elegido = enteroAleatorio(0, direccionesSeguras.size()-1);
    return direccionesSeguras.at(elegido);
}