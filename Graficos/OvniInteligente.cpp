#include <iostream>
#include "OvniInteligente.hpp"

//Red neural que se usara para esquivar asteroides
neural::Network redInteligente(12, 1, {24});

OvniInteligente::OvniInteligente(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs) :
        Ovni(limitesPantalla, color, cs) {
    radio = radio * 3 / 4;
    SonidoPresencia = ControladorSonido::OVNI_PEQUENO;
    SonidoDestruccion = ControladorSonido::EXP_1;
    redInteligente.read(fichero);
}

OvniInteligente::~OvniInteligente() {}

void OvniInteligente::disparar(sf::Vector2f nave) {
    if (estado == VIVO) {
        if (num_disparos < MAX_DISPAROS) {
            sf::Vector2f vectorDir = (nave - posicion);
            float direccionDisp = atan2f(vectorDir.y, vectorDir.x);
            disparos[num_disparos] = Disparo(posicion, direccion, limites, color);
            direccionDisp = direccionDisp + valorAleatorio(-error, error);
            disparos[num_disparos].setDireccion(direccionDisp);
            num_disparos++;
        }
        cs->reproducir(SonidoDisparo);
    }
}

void OvniInteligente::mover(std::vector<Asteroide> &v, Triangular &n) {
    if (estado == VIVO) {
        std::uniform_real_distribution<float> distributionGirar(0, 1);
        vector<Asteroide *> asteroidePeligroso = asteroideMasCercano(posicion, v);
        vector<double> entradasRed;
        if (asteroidePeligroso.size() == 3) {
            entradasRed = {asteroidePeligroso[0]->getPosicion().x - posicion.x,
                           posicion.y - asteroidePeligroso[0]->getPosicion().y,
                           asteroidePeligroso[0]->getVelocidad().x,
                           asteroidePeligroso[0]->getVelocidad().y,
                           asteroidePeligroso[1]->getPosicion().x - posicion.x,
                           posicion.y - asteroidePeligroso[1]->getPosicion().y,
                           asteroidePeligroso[1]->getVelocidad().x,
                           asteroidePeligroso[1]->getVelocidad().y,
                           asteroidePeligroso[2]->getPosicion().x - posicion.x,
                           posicion.y - asteroidePeligroso[2]->getPosicion().y,
                           asteroidePeligroso[2]->getVelocidad().x,
                           asteroidePeligroso[2]->getVelocidad().y,};
        } else if (asteroidePeligroso.size() == 2) {
            entradasRed = {asteroidePeligroso[0]->getPosicion().x - posicion.x,
                           posicion.y - asteroidePeligroso[0]->getPosicion().y,
                           asteroidePeligroso[0]->getVelocidad().x,
                           asteroidePeligroso[0]->getVelocidad().y,
                           asteroidePeligroso[1]->getPosicion().x - posicion.x,
                           posicion.y - asteroidePeligroso[1]->getPosicion().y,
                           asteroidePeligroso[1]->getVelocidad().x,
                           asteroidePeligroso[1]->getVelocidad().y,
                           -99999.0,
                           -99999.0,
                           0.0,
                           0.0,};
        } else if (asteroidePeligroso.size() == 1) {
            entradasRed = {asteroidePeligroso[0]->getPosicion().x - posicion.x,
                           posicion.y - asteroidePeligroso[0]->getPosicion().y,
                           asteroidePeligroso[0]->getVelocidad().x,
                           asteroidePeligroso[0]->getVelocidad().y,
                           -99999.0,
                           -99999.0,
                           0.0,
                           0.0,
                           -99999.0,
                           -99999.0,
                           0.0,
                           0.0,};
        } else {
            entradasRed = {-99999.0,
                           -99999.0,
                           0.0,
                           0.0,
                           -99999.0,
                           -99999.0,
                           0.0,
                           0.0,
                           -99999.0,
                           -99999.0,
                           0.0,
                           0.0,};
        }
        direccion = redInteligente.run(entradasRed)[0];
        /*if (valorAleatorio() < 0.0055) {
            direccion = anguloAleatorio();
        }*/
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
            disparar(n.posicion);
        }

        //Colision del ovni con un asteroide
        for (int i = 0; i < v.size(); i++) {
            if (comprobarColision(v[i])) {
                cambiarEstado(EXP1);
                //Destruir asteroide, dividirlo o lo que sea....
                v[i].gestionarDestruccion(v);
                v.erase(v.begin() + i);
                i--;
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
            if ((n.getEstado() == REPOSO || n.getEstado() == ACELERANDO) && disparos[i].comprobarColision(n)) {
                recuperarDisparo(i);
                i--;
                n.cambiarEstado(DESTRUIDA);
                continue;
            }

            for (int j = 0; j < v.size(); j--) {
                if (disparos[i].comprobarColision(v[j])) {
                    recuperarDisparo(i);
                    i--;
                    //Destruir asteroide, dividirlo o lo que sea....
                    v[j].gestionarDestruccion(v);
                    v.erase(v.begin() + j);
                    j--;
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
        error = error - PI / 36;
    } else {
        error = 0.0;
    }
}

int OvniInteligente::getPuntuacion() const {
    return 1000;
}