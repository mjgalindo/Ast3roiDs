#include <string>
#include <iostream>
#include "OvniInteligente3D.hpp"

using namespace std;
using namespace sf;

neural::Network red3D(1,1);

OvniInteligente3D::OvniInteligente3D(ControladorSonido *controladorSonido, float limitesMovimiento) :
        Ovni3D(controladorSonido, limitesMovimiento) {

    pos.escala = {0.5f, 0.5f, 0.5f};
    red3D = red3D.read(fichero);
    sonidoOvni = ControladorSonido::OVNI_PEQUENO;
}


void OvniInteligente3D::actualizar(int nivel, std::vector<Asteroide3D> &asteroides, Elemento3D &nave) {
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
            disparar(nave);
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
            nave.destruir();
        }

        if (colisionado || disparos[i].estado == DESTRUIDO_3D) {
            disparos.erase(disparos.begin() + i);
            i--;
        }

    }

}

void OvniInteligente3D::disparar(Elemento3D nave) {
    vector<double> dir = {nave.pos.posicion.x-pos.posicion.x,nave.pos.posicion.y-pos.posicion.y,nave.pos.posicion.z-pos.posicion.z};
    vector<double> salida = red3D.run(dir);
    glm::vec3 dirDisp = glm::normalize(glm::vec3(salida.at(0),salida.at(1),salida.at(2)));
    disparos.emplace_back(dirDisp, pos.posicion, pos.rotacion, limiteMovimiento);
    disparos.back().cambioDisparoEsferico();

    csonido->reproducir(ControladorSonido::DISPARO,true);
}

glm::vec3 OvniInteligente3D::direccionSegura(glm::vec3 posicion, std::vector<Asteroide3D> v) {
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
        velocidadAux = direcciones[i] * vMax;
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
            distanciaRecorrida += vMax / 60.0f;
        }
        if (!choque) {
            if (direcciones[i] == direccion) {
                return direccion;
            }
            direccionesSeguras.push_back((direcciones[i]));
        }
        for (int j = 0; j < posiciones.size(); j++) {
            v[j].pos.posicion = posiciones[j];
        }
    }
    if (direccionesSeguras.size() == 0) {
        return direccion;
    }
    int elegido = enteroAleatorio(0, (int) direccionesSeguras.size() - 1);
    return direccionesSeguras[elegido];
}

int OvniInteligente3D::getPuntuacion() const {
    return 1000;
}