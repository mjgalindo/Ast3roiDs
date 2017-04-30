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
    sonidoOvni = ControladorSonido::OVNI_GRANDE;
}

void Ovni3D::actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Elemento3D &nave) {
    if(estado == VIVO) {
        if(valorAleatorio(0.0f,1.0f)) {
            direccion = direccionSegura(pos.posicion,asteroides);
            velocidad = direccion * VELOCIDAD_INICIAL;
        }
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
            if (asteroides[i].estado == NORMAL && colisionEsferaEsfera(pos.posicion, 7.6f * pos.escala.z, asteroides[i].pos.posicion,
                                     Asteroide3D::RADIO * asteroides[i].pos.escala.y)) {
                //COLISION!!!!!!!!!!!!
                asteroides[i].colisionDetectada(nivel, asteroides);
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

    // Actualiza los disparos del ovni
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
                disparos[i].estado = DESTRUIDO;
                break;
            }
        }

        //Se comprueba la colision de los disparos con la nave
        if(disparos[i].estado != DESTRUIDO && nave.estado == NORMAL && colisionPuntoEsfera(disparos[i].pos.posicion, nave.pos.posicion, 7.6f*nave.pos.escala.z)){
            disparos[i].estado = DESTRUIDO;
            nave.destruir();
        }

        if (disparos[i].estado == DESTRUIDO) {
            disparos.erase(disparos.begin() + i);
            i--;
        }

    }

}

void Ovni3D::dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar, sf::RenderStates states) const {
    if(estado == VIVO) {
        Elemento3D::dibujar(target, camara, rellenar, states);
    }
    // Dibuja los disparos
    for (const Disparo3D &disparo : disparos)
        disparo.dibujar(target, camara, rellenar, states);
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
        direccion = direcciones[enteroAleatorio(0, (int)direcciones.size()-1)];
        velocidad = VELOCIDAD_INICIAL*direccion;
        csonido->reproducir(sonidoOvni,false);
    } else if(estado == MUERTO) {
        csonido->detener(sonidoOvni);
    }
}

glm::vec3 Ovni3D::direccionSegura(glm::vec3 posicion, std::vector<Asteroide3D> v) {
    float vMax = VELOCIDAD_INICIAL;
    float radioPeligro = 20.0f;
    vector<glm::vec3> direccionesSeguras;
    vector<glm::vec3> posiciones;
    for (int i = 0; i < v.size(); i++) {
        posiciones.push_back(v[i].pos.posicion);
    }
    glm::vec3 posicionAux, velocidadAux;
    for (unsigned long long i = 0; i < direcciones.size(); i++) {
        posicionAux = posicion;
        velocidadAux = direcciones[i]*vMax;
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
                v[j].actualizar();
                if ((v[j].estado == NORMAL && colisionEsferaEsfera(posicionAux, 7.6f * pos.escala.z, v[j].pos.posicion,
                                                                               Asteroide3D::RADIO * v[j].pos.escala.y))) {
                    choque = true;
                    break;
                }
            }
            distanciaRecorrida += vMax/60.0f;
        }
        if (!choque) {
            if (direcciones[i] == direccion) {
                return direccion;
            }
            direccionesSeguras.push_back((direcciones[i]));
        }
        for (int j = 0; j < posiciones.size(); j++) {
            v[j].pos.posicion=posiciones[j];
        }
    }
    if (direccionesSeguras.size() == 0) {
        return direccion;
    }
    int elegido = enteroAleatorio(0,(int)direccionesSeguras.size()-1);
    return direccionesSeguras[elegido];
}

int Ovni3D::getPuntuacion() const {
    return 200;
}