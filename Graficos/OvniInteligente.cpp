#include <iostream>
#include "OvniInteligente.hpp"

using namespace std;

OvniInteligente::OvniInteligente(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs) :
        Ovni(limitesPantalla, color, cs) {
    radio = radio * 3 / 4;
    SonidoPresencia = ControladorSonido::OVNI_PEQUENO;
    SonidoDestruccion = ControladorSonido::EXP_1;
}

OvniInteligente::~OvniInteligente() {}

void OvniInteligente::disparar(sf::Vector2f nave) {
    if (estado == VIVO) {
        if (num_disparos < MAX_DISPAROS) {
            sf::Vector2f vectorDir = (nave - posicion);
            float direccionDisp = atan2f(vectorDir.y, vectorDir.x);
            disparos[num_disparos] = Disparo(posicion, (float) direccion, limites, color);
            direccionDisp = direccionDisp + valorAleatorio(-error / 5, error / 5);
            disparos[num_disparos].setDireccion(direccionDisp);
            num_disparos++;
        }
        cs->reproducir(SonidoDisparo);
    }
}

void OvniInteligente::mover(std::vector<Asteroide> &astds, Triangular &nave) {
    if (estado == VIVO) {
        direccion = direccionSegura(sf::CircleShape(radio), posicion, astds);

        posicion.x += VELOCIDAD * cos(direccion) * limites.y / (float) RESOLUCION_BASE.y;
        if (posicion.x - 1 >= limites.x) {
            posicion.x -= limites.x;
        } else if (posicion.x + 1 <= 0.0) {
            posicion.x += limites.x;
        }

        posicion.y += VELOCIDAD * sin(direccion) * limites.y / (float) RESOLUCION_BASE.y;
        if (posicion.y - 1 >= limites.y) {
            posicion.y -= limites.y;
        } else if (posicion.y + 1 <= 0.0) {
            posicion.y += limites.y;
        }

        if (num_disparos < 2 && enteroAleatorio(0, 100) == 0) {
            disparar(nave.posicion);
        }

        //Colision del ovni con un asteroide
        for (int i = 0; i < astds.size(); i++) {
            if (comprobarColision(astds[i])) {
                cambiarEstado(EXP1);
                //Destruir asteroide, dividirlo o lo que sea....
                astds[i].gestionarDestruccion(astds);
            }
        }

        //Mover los disparos
        for (int i = 0; i < num_disparos; i++) {
            disparos[i].mover();

            if (disparos[i].comprobarAlcance()) {
                recuperarDisparo(i);
                i--;
                continue;
            }

            //Se comprueba el impacto de los disparos
            if ((nave.getEstado() == REPOSO || nave.getEstado() == ACELERANDO) && disparos[i].comprobarColision(nave)) {
                recuperarDisparo(i);
                i--;
                nave.cambiarEstado(DESTRUIDA);
                continue;
            }

            for (int j = 0; j < astds.size(); j++) {
                if (astds[j].estado == MOVIMIENTO && disparos[i].comprobarColision(astds[j])) {
                    recuperarDisparo(i);
                    i--;
                    //Destruir asteroide, dividirlo o lo que sea....
                    astds[j].gestionarDestruccion(astds);
                    break;
                }
            }
        }
    }
    if (estado == EXP1) {
        if (recienDestruida) {
            posicion0 = posicion;
            posicion1 = posicion;
            posicion2 = posicion;
            posicion3 = posicion;
            posicion4 = posicion;
            posicion5 = posicion;
            posicion6 = posicion;
            posicion7 = posicion;
            recienDestruida = false;
            start = clock();
        }
        double tiempo = (clock() - start) / (double) CLOCKS_PER_SEC;
        if (tiempo > 2.0) {
            estado = MUERTO;
            //cambiarEstado(MUERTO,{0, 0});
        }
        posicion0 = {posicion0.x + 1.0f, posicion0.y + 1.0f};
        posicion1 = {posicion1.x + 1.2f, posicion1.y + 1.1f};
        posicion2 = {posicion2.x + 1.0f, posicion2.y - 1.2f};
        posicion3 = {posicion3.x - 0.5f, posicion3.y - 1.0f};
        posicion4 = {posicion4.x + 0.75f, posicion4.y + 0.6f};
        posicion5 = {posicion5.x - 0.65f, posicion5.y + 0.45f};
        posicion6 = {posicion6.x + 0.4f, posicion6.y - 0.2f};
        posicion7 = {posicion7.x - 0.9f, posicion7.y - 0.3f};
    }
}

void OvniInteligente::disminuirError() {
    if (error > 0.0) {
        error = (float) (error - PI / 36);
    } else {
        error = 0.0;
    }
}

int OvniInteligente::getPuntuacion() const {
    return 1000;
}

double OvniInteligente::direccionSegura(sf::CircleShape ovni, sf::Vector2f posicionSegura, std::vector<Asteroide> v) {
    float vMax = VELOCIDAD;
    float radioPeligro = 60.0f;
    ovni.setRadius(radio);
    vector<double> direccionesSeguras;
    vector<sf::Vector2f> posiciones;
    for (auto ast = v.begin(); ast != v.end(); ++ast) {
        posiciones.push_back(ast->getPosicion());
    }
    for (unsigned long long i = 0; i < direcciones.size(); i++) {
        ovni.setPosition(posicionSegura);
        bool choque = false;
        float distanciaRecorrida = 0.0f;
        while (distanciaRecorrida < radioPeligro && !choque) {
            //MOVER OVNI Y COMPROBAR QUE CHOCA
            ovni.move({vMax * (float) cos(direcciones.at(i)) * ratio(limites),
                       vMax * (float) sin(direcciones.at(i) * ratio(limites))});
            sf::Vector2f posicionOvni = ovni.getPosition();
            // Evita los limites del espacio
            if (posicionOvni.x + 1 <= 0.0) {
                posicionOvni.x += limites.x;
            } else if (posicionOvni.x - 1 >= limites.x) {
                posicionOvni.x -= limites.x;
            }

            if (posicionOvni.y + 1 <= 0, 0) {
                posicionOvni.y += limites.y;
            } else if (posicionOvni.y - 1 >= limites.y) {
                posicionOvni.y -= limites.y;
            }
            ovni.setPosition(posicionOvni);
            for (auto ast = v.begin(); ast != v.end(); ++ast) {
                ast->mover();
                if (colisionCirculos(posicionOvni, ovni.getRadius(), ast->getPosicion(), ast->getRadio())) {
                    // Hay colision, se informa a la red y se reinicia la escena aleatoriamente
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
            v[j].setPosicion(posiciones[j]);
        }
    }
    if (direccionesSeguras.size() == 0) {
        return ultimaDireccion;
    }
    int elegido = enteroAleatorio(0, direccionesSeguras.size());
    ultimaDireccion = direccionesSeguras[elegido];
    return direccionesSeguras[elegido];
}