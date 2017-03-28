#include "Ovni.hpp"
#include <iostream>

Ovni::Ovni(sf::Vector2u limitesPantalla, sf::Color color) :
        Circular({0, 0}, 15 * limitesPantalla.y / (float) RESOLUCION_BASE.y), color(color) {
    estado = MUERTO;
    if (!bufferSonidoDisparo.loadFromFile("Recursos/Sonido/fire.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/fire.wav\"");
    }
    if (!bufferSonidoOvni.loadFromFile("Recursos/Sonido/saucerBig.wav")) {
        throw std::invalid_argument("No se pudo encontrar el fichero \"Recursos/Sonido/thrust.wav\"");
    }

    reproductorDeSonidoOvni.setBuffer(bufferSonidoOvni);
    reproductorDeSonidoDisparos.setBuffer(bufferSonidoDisparo);

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
}

Ovni::~Ovni() {}

float Ovni::getDireccion() {
    return direccion;
}

sf::Vector2f Ovni::getVelocidad() {
    return velocidad;
}

int Ovni::getPuntuacion() const {
    return 1000;
}

void Ovni::disparar() {
    if (estado == VIVO) {
        if (num_disparos < MAX_DISPAROS) {
            disparos[num_disparos] = Disparo(posicion, direccion, limites, color);
            disparos[num_disparos].setDireccion(anguloAleatorio());
            num_disparos++;
        }
        reproductorDeSonidoDisparos.play();
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

void Ovni::mover(std::vector<Asteroide> &v, Triangular &n) {
    if (estado == VIVO) {
        std::uniform_real_distribution<float> distributionGirar(0, 1);
        if (valorAleatorio() < 0.0055) {
            direccion = anguloAleatorio();
        }
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
            reproductorDeSonidoOvni.setLoop(false);
            reproductorDeSonidoOvni.stop();

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
                reproductorDeSonidoOvni.setLoop(true);
                reproductorDeSonidoOvni.play();
            }
            break;
    }
    ciclo++;
}
