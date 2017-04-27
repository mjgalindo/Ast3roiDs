#include <iostream>
#include "OvniInteligente.hpp"

using namespace std;


neural::Network red(1,1);

OvniInteligente::OvniInteligente(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs) :
        Ovni(limitesPantalla, color, cs) {
    radio = radio * 3 / 4;
    SonidoPresencia = ControladorSonido::OVNI_PEQUENO;
    SonidoDestruccion = ControladorSonido::EXP_1;
    red = red.read(ficheroRed);
    ocultas = red.getFirstLayer()->size();
    capaOculta = red.getFirstLayer();     //Capa oculta de la red
    for(int i = 0; i < ocultas; i++) {
        contexto.push_back(0);
    }
}

OvniInteligente::~OvniInteligente() {}

void OvniInteligente::disparar(sf::Vector2f nave) {
    if (estado == VIVO) {
        if (num_disparos < MAX_DISPAROS) {
            sf::Vector2f vectorDir = (nave - posicion);
            if((abs(vectorDir.x) > limites.x/2)) {
                if(vectorDir.x > 0.0f) {
                    vectorDir.x = -posicion.x - (limites.x - nave.x);
                } else {
                    vectorDir.x = posicion.x + limites.x + nave.x;
                }
            }
            if((abs(vectorDir.y) > limites.y/2)) {
                if(vectorDir.y > 0.0f) {
                    vectorDir.y = -posicion.y - (limites.y - nave.y);
                } else {
                    vectorDir.y = posicion.y + limites.y + nave.y;
                }
            }
            double direccionDisp = atan2f(vectorDir.y, vectorDir.x);
            direccionDisp = output2RadiansDisparo(red.run({vectorDir.x,vectorDir.y}));
            disparos[num_disparos] = Disparo(posicion, (float) direccion, limites, color);
            direccionDisp = direccionDisp + valorAleatorio(-error / 5, error / 5);
            disparos[num_disparos].setDireccion((float)direccionDisp);
            num_disparos++;
        }
        cs->reproducir(SonidoDisparo);
    }
}

double OvniInteligente::output2RadiansDisparo(vector<double> output) {
    vector<int> salidaEntero;
    for(int i = 0; i < output.size(); i++) {
        if(output.at(i) >= 0) {
            salidaEntero.push_back(1);
        } else {
            salidaEntero.push_back(0);
        }
    }
    switch(salidaEntero.at(0)) {
        case 0:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 0.0;
                                        case 1:
                                            return -PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -PI/8;

                                        case 1:
                                            return -3*PI/16;
                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -PI/4;

                                        case 1:

                                            return -5*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -3*PI/8;

                                        case 1:
                                            return -7*PI/16;
                                    }
                            }
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -PI/2;

                                        case 1:

                                            return -9*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -10*PI/16;

                                        case 1:
                                            return -11*PI/16;
                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -3*PI/4;

                                        case 1:
                                            return -13*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -7*PI/8;

                                        case 1:
                                            return -15*PI/16;
                                    }
                            }
                    }
            }
        case 1:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI;
                                        case 1:
                                            return PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI/8;

                                        case 1:
                                            return 3*PI/16;
                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI/4;

                                        case 1:

                                            return 5*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 3*PI/8;

                                        case 1:
                                            return 7*PI/16;
                                    }
                            }
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI/2;

                                        case 1:

                                            return 9*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 10*PI/16;

                                        case 1:
                                            return 11*PI/16;

                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 3*PI/4;

                                        case 1:
                                            return 13*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 7*PI/8;

                                        case 1:
                                            return 15*PI/16;
                                    }
                            }
                    }
            }
    }
}


double OvniInteligente::output2RadiansMover(vector<double> output) {
    vector<int> salidaEntero;
    for(int i = 0; i < output.size(); i++) {
        if(output.at(i) >= 0) {
            salidaEntero.push_back(1);
        } else {
            salidaEntero.push_back(0);
        }
    }
    switch(salidaEntero.at(0)) {
        case 0:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return 0.0;
                        case 1:
                            return -PI/4;
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return -PI/2;
                        case 1:
                            return -3*PI/4;
                    }
            }
        case 1:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return PI;
                        case 1:
                            return PI/4;
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return PI/2;
                        case 1:
                            return 3*PI/4;
                    }
            }
    }
}

std::vector<Asteroide *> OvniInteligente::asteroideMasCercano(sf::Vector2f posicion, std::vector<Asteroide> asteroides) {
    double distanciaMenor1 = 99999999.0;
    double distanciaMenor2 = 99999999.0;
    double distanciaMenor3 = 99999999.0;
    double distanciaMenor4 = 99999999.0;
    Asteroide *masCercano1 = 0, *masCercano2 = 0, *masCercano3 = 0, *masCercano4 = 0;;
    std::vector<Asteroide *> masCercanos;
    for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
        double distanciatmp = distancia(ast->getPosicion(), posicion);
        if (distanciatmp < distanciaMenor1) {
            distanciaMenor4 = distanciaMenor3;
            masCercano4 = masCercano3;
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciaMenor1;
            masCercano2 = masCercano1;
            distanciaMenor1 = distanciatmp;
            masCercano1 = ast.base();
        } else if(distanciatmp < distanciaMenor2) {
            distanciaMenor4 = distanciaMenor3;
            masCercano4 = masCercano3;
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciatmp;
            masCercano2 = ast.base();
        } else if(distanciatmp < distanciaMenor3) {
            distanciaMenor4 = distanciaMenor3;
            masCercano4 = masCercano3;
            distanciaMenor3 = distanciatmp;
            masCercano3 = ast.base();
        } else if(distanciatmp < distanciaMenor4) {
            distanciaMenor4 = distanciatmp;
            masCercano4 = ast.base();
        }
    }
    masCercanos.push_back(masCercano1);
    masCercanos.push_back(masCercano2);
    masCercanos.push_back(masCercano3);
    masCercanos.push_back(masCercano4);
    return masCercanos;
}

void OvniInteligente::mover(std::vector<Asteroide> &astds, Triangular &nave) {
    if (estado == VIVO) {
        direccion = direccionSegura(sf::CircleShape(radio), posicion, astds);
        /*vector<Asteroide *> asteroidePeligroso = asteroideMasCercano(posicion,astds);
        vector<double> entradasRed{asteroidePeligroso[0]->getPosicion().x - posicion.x,
                                   asteroidePeligroso[0]->getPosicion().y - posicion.y,
                                   asteroidePeligroso[0]->getVelocidad().x,
                                   asteroidePeligroso[0]->getVelocidad().y,
                                   asteroidePeligroso[1]->getPosicion().x - posicion.x,
                                   asteroidePeligroso[1]->getPosicion().y - posicion.y,
                                   asteroidePeligroso[1]->getVelocidad().x,
                                   asteroidePeligroso[1]->getVelocidad().y,
                                   asteroidePeligroso[2]->getPosicion().x - posicion.x,
                                   asteroidePeligroso[2]->getPosicion().y - posicion.y,
                                   asteroidePeligroso[2]->getVelocidad().x,
                                   asteroidePeligroso[2]->getVelocidad().y};
        entradasRed.insert(entradasRed.end(),contexto.begin(),contexto.end());
        direccion = output2RadiansMover(red.run(entradasRed));
        contexto = capaOculta->Output();*/    //Se actualiza el valor de neuronas de contexto
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
    int elegido = enteroAleatorio(0, direccionesSeguras.size()-1);
    ultimaDireccion = direccionesSeguras[elegido];
    return direccionesSeguras[elegido];
}