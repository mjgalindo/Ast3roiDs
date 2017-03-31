#include "Ovni.hpp"

//Red neural que se usara para esquivar asteroides
neural::Network redNormal(12, 1, {24});

Ovni::Ovni(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs) :
        Circular({0, 0}, 15 * limitesPantalla.y / (float) RESOLUCION_BASE.y), color(color), cs(cs) {

    estado = MUERTO;

    SonidoPresencia = ControladorSonido::OVNI_GRANDE;
    SonidoDestruccion = ControladorSonido::EXP_2;

    num_disparos = 0;

    poligono.setPrimitiveType(sf::LineStrip);
    poligono.resize(12);
    poligono[0].position = {-1.0f, 0.0f};
    poligono[1].position = {1.0f, 0.0f};
    poligono[2].position = {0.6f, -0.4f};
    poligono[3].position = {-0.6f, -0.4f};
    poligono[4].position = {-1.0f, 0.0f};
    poligono[5].position = {-0.6f, 0.4f};
    poligono[6].position = {0.6f, 0.4f};
    poligono[7].position = {1.0f, 0.0f};
    poligono[8].position = {0.6f, -0.4f};
    poligono[9].position = {0.4f, -0.8f};
    poligono[10].position = {-0.4f, -0.8f};
    poligono[11].position = {-0.6f, -0.4f};

    for (int i = 0; i < poligono.getVertexCount(); i++) {
        poligono[i].color = color;
    }

    limites = limitesPantalla;
    punto.setPrimitiveType(sf::LineStrip);
    punto.resize(2);
    punto[0].position = {0.0f, 0.0f};
    punto[1].position = {1.0f * limitesPantalla.y / (float) RESOLUCION_BASE.y,
                         1.0f * limitesPantalla.y / (float) RESOLUCION_BASE.y};
    punto[0].color = color;
    punto[1].color = color;
    recienDestruida = true;

    redNormal.read(fichero);
}

Ovni::~Ovni() {
    cs->detener(SonidoDestruccion);
    cs->detener(SonidoPresencia);
}

double Ovni::distancia(sf::Vector2f a, sf::Vector2f b) {
    double distanciaX = (a.x - b.x);
    double distanciaY = (a.y - b.y);
    if ((limites.x + a.x) - b.x < abs(distanciaX)) {
        distanciaX = (limites.x + a.x) - b.x;
    }
    if ((limites.y + a.y) - b.y < abs(distanciaY)) {
        distanciaY = (limites.y + a.y) - b.y;
    }
    return sqrt(distanciaX * distanciaX + (distanciaY * distanciaY));
}

vector<Asteroide *> Ovni::asteroideMasCercano(sf::Vector2f posicion, vector<Asteroide> asteroides) {
    double distanciaMenor1 = 99999999.0;
    double distanciaMenor2 = 99999999.0;
    double distanciaMenor3 = 99999999.0;
    Asteroide *masCercano1 = 0, *masCercano2 = 0, *masCercano3 = 0;
    vector<Asteroide *> masCercanos;
    for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
        double distanciatmp = distancia(ast->getPosicion(), posicion);
        if (distanciatmp < distanciaMenor1) {
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciaMenor1;
            masCercano2 = masCercano1;
            distanciaMenor1 = distanciatmp;
            masCercano1 = ast.base();
        } else if (distanciatmp < distanciaMenor2) {
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciatmp;
            masCercano2 = ast.base();
        } else if (distanciatmp < distanciaMenor3) {
            distanciaMenor3 = distanciatmp;
            masCercano3 = ast.base();
        }
    }
    if (distanciaMenor1 != 99999999.0) {
        masCercanos.push_back(masCercano1);
    }
    if (distanciaMenor2 != 99999999.0) {
        masCercanos.push_back(masCercano2);
    }
    if (distanciaMenor3 != 99999999.0) {
        masCercanos.push_back(masCercano3);
    }
    return masCercanos;
}

float Ovni::getDireccion() {
    return direccion;
}

sf::Vector2f Ovni::getVelocidad() {
    return velocidad;
}

int Ovni::getPuntuacion() const {
    return 300;
}

void Ovni::disparar() {
    if (estado == VIVO) {
        if (num_disparos < MAX_DISPAROS) {
            disparos[num_disparos] = Disparo(posicion, direccion, limites, color);
            disparos[num_disparos].setDireccion(anguloAleatorio());
            num_disparos++;
        }
        cs->reproducir(SonidoDisparo, true);
    }
}

void Ovni::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (estado == VIVO) {
        sf::Transform t;
        t.translate(posicion).scale({radio, radio});
        target.draw(poligono, t);
    } else if (estado == EXP1) {
        sf::Transform t0, t1, t2, t3, t4, t5, t6, t7;
        t0.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion0);
        t1.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion1);
        t2.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion2);
        t3.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion3);
        t4.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion4);
        t5.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion5);
        t6.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion6);
        t7.rotate(direccion * (180.0f / 3.14f), posicion).translate(posicion7);


        target.draw(punto, t0);
        target.draw(punto, t1);
        target.draw(punto, t2);
        target.draw(punto, t3);
        target.draw(punto, t4);
        target.draw(punto, t5);
        target.draw(punto, t6);
        target.draw(punto, t7);
    }

    for (int i = 0; i < num_disparos; i++) {
        target.draw(disparos[i]);
    }
}

double Ovni::network2Radianes(double salida) {
    double angulo = 0.0;
    if (salida < -3 * (2.0 / 8.0)) {
        angulo = PI * 3 / 4;
        //cout << "UL ";
    } else if (salida < -2 * (2.0 / 8.0)) {
        angulo = PI;
        //cout << "L ";
    } else if (salida < -1 * (2.0 / 8.0)) {
        angulo = -PI * 3 / 4;
        //cout << "DL ";
    } else if (salida < 0 * (2.0 / 8.0)) {
        angulo = PI / 2;
        //cout << "U ";
    } else if (salida < 1 * (2.0 / 8.0)) {
        angulo = PI / 4;
        //cout << "UR ";
    } else if (salida < 2 * (2.0 / 8.0)) {
        angulo = 0;
        //cout << "R ";
    } else if (salida < 3 * (2.0 / 8.0)) {
        angulo = -PI / 4;
        //cout << "DR ";
    } else if (salida < 4 * (2.0 / 8.0)) {
        angulo = -PI / 2;
        //cout << "D ";
    }
    return angulo;
}

void Ovni::mover(std::vector<Asteroide> &v, Triangular &n) {
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
        direccion = network2Radianes(redNormal.run(entradasRed)[0]);
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

        if (num_disparos<2 && enteroAleatorio(0, 100)==0) {
            disparar();
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

void Ovni::recuperarDisparo(int d) {
    for (int i = d; i < num_disparos - 1; i++) {
        disparos[i] = disparos[i + 1];
    }
    num_disparos--;
}

bool Ovni::comprobarColision(Circular &c) {
    return colisionCirculos(posicion, radio, c.posicion, c.radio);
}

void Ovni::cambiarEstado(int nuevoEstado) {
    static int ciclo = 0;
    estado = nuevoEstado;
    switch ((EstadoOvni) nuevoEstado) {
        case VIVO:
            ciclo = 0;
            break;
        case EXP1:
            num_disparos = 0;
            if (recienDestruida) {
                cs->reproducir(SonidoDestruccion);
                cs->detener(SonidoPresencia);
            }
            break;
        case MUERTO:
            if (rand() % 200 == 0) {
                estado = VIVO;
                if (valorAleatorio() < 0.5) {
                    posicion = {30.0f * (limites.x / (float) RESOLUCION_BASE.x), valorAleatorio(0, limites.y)};
                } else {
                    std::uniform_real_distribution<float> distributionX(0, limites.x);
                    posicion = {valorAleatorio(0, limites.x), 30.0f * (limites.y / (float) RESOLUCION_BASE.y)};
                }
                direccion = anguloAleatorio();
                num_disparos = 0;
                recienDestruida = true;
                cs->reproducir(SonidoPresencia);
            }
            break;
        default:
            break;
    }
    ciclo++;
}
