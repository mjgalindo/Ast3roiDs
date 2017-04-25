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
    pos.escala = {3.0f, 3.0f, 3.0f};
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
        velocidad = direccionSegura(pos.posicion,asteroides) * VELOCIDAD_INICIAL;
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
                asteroides[i].colisionDetectada(nivel, asteroides);
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
        if (colisionEsferaEsfera(pos.posicion, 4.8f * pos.escala.y , nave.pos.posicion, 7.6f * nave.pos.escala.z)) {
            //COLISION
            nave.destruir();
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
        pos.posicion = {valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f)};
        direccion = glm::vec3(valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f),valorAleatorio(-1.0f,1.0f));
        ultimaDireccion = direccion;
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
    for (auto ast = v.begin(); ast != v.end(); ++ast) {
        posiciones.push_back(ast->pos.posicion);
    }
    glm::vec3 posicionAux, velocidadAux;
    for (unsigned long long i = 0; i < direcciones.size(); i++) {
        posicion = posicionAux;
        velocidadAux = direcciones.at(i)*vMax;
        bool choque = false;
        float distanciaRecorrida = 0.0f;
        while (distanciaRecorrida < radioPeligro && !choque) {
            //MOVER OVNI Y COMPROBAR QUE CHOCA
            posicionAux = posicionAux + velocidadAux;
            // Evita los limites del espacio
            if (distanciaEuclidea(posicionAux, glm::vec3{0, 0, 0}) > limiteMovimiento) {
                posicionAux = glm::vec3{0, 0, 0} - posicionAux;
                while (distanciaEuclidea(posicionAux, glm::vec3{0, 0, 0}) > limiteMovimiento) {
                    posicionAux.x = (abs(posicionAux.x) - 0.1f) * posicionAux.x / abs(posicionAux.x);
                    posicionAux.y = (abs(posicionAux.y) - 0.1f) * posicionAux.y / abs(posicionAux.y);
                    posicionAux.z = (abs(posicionAux.z) - 0.1f) * posicionAux.z / abs(posicionAux.z);
                }
            }
            for (auto ast = v.begin(); ast != v.end(); ++ast) {
                ast->actualizar();
                if (colisionEsferaEsfera(posicionAux, 7.6f * this->pos.escala.z, v[i].pos.posicion,
                                         1.0f * v[i].pos.escala.y)) {
                    choque = true;
                    break;
                }
            }
            distanciaRecorrida += vMax;
        }
        if (!choque) {
            if (direcciones[i] == ultimaDireccion) {
                return ultimaDireccion;
            }
            direccionesSeguras.push_back(direcciones[i]);
        }
        for (int j = 0; j < posiciones.size(); j++) {
            v[j].pos.posicion=posiciones[j];
        }
    }
    if (direccionesSeguras.size() == 0) {
        return ultimaDireccion;
    }
    int elegido = enteroAleatorio(0, direccionesSeguras.size());
    ultimaDireccion = direccionesSeguras[elegido];
    return direccionesSeguras[elegido];
}