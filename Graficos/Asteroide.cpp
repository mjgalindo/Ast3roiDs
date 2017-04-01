#include <iostream>
#include "Asteroide.hpp"

static constexpr float tamanosReales[] = {7.25f, 12.5f, 25.0f};

Asteroide::Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, Tipo tipo, Tamano tam,
                     sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs) :
        Circular(posicion_inicial, tamanosReales[tam] * (limitesPantalla.y / (float) RESOLUCION_BASE.y)), color(color),
        cs(cs) {
    direccion = dir;
    velocidad = vel;
    version = tipo;
    tipoTamano = tam;
    limites = limitesPantalla;
    // Definimos el asteroide como una serie de puntos conectados por orden
    poligono.setPrimitiveType(sf::LineStrip);
    switch (version) {
        case TIPO_0:
            poligono.resize(11);
            poligono[0].position = {-0.888889f, -0.422222f};
            poligono[1].position = {-0.911111f, -0.274074f};
            poligono[2].position = {-0.348148f, 0.62963f};
            poligono[3].position = {0.318519f, 0.644444f};
            poligono[4].position = {0.962963f, 0.244444f};
            poligono[5].position = {0.718519f, -0.0740741f};
            poligono[6].position = {0.703704f, -0.614815f};
            poligono[7].position = {0.466667f, -1.f};
            poligono[8].position = {0.037037f, -0.57037f};
            poligono[9].position = {-0.422222f, -0.962963f};
            poligono[10].position = {-0.888889f, -0.422222f};
            break;
        case TIPO_1:
            poligono.resize(13);
            poligono[0].position = {-0.37037f, -0.691358f};
            poligono[1].position = {-0.154321f, -0.339506f};
            poligono[2].position = {-0.709877f, -0.339506f};
            poligono[3].position = {-0.728395f, 0.185185f};
            poligono[4].position = {-0.234568f, 0.740741f};
            poligono[5].position = {0.246914f, 0.54321f};
            poligono[6].position = {0.419753f, 0.771605f};
            poligono[7].position = {0.753086f, 0.339506f};
            poligono[8].position = {0.320988f, 0.0617284f};
            poligono[9].position = {0.814815f, -0.123457f};
            poligono[10].position = {1.f, -0.339506f};
            poligono[11].position = {0.259259f, -0.666667f};
            poligono[12].position = {-0.37037f, -0.691358f};
            break;
        case TIPO_2:
            poligono.resize(12);
            poligono[0].position = {-0.362205f, -0.88189f};
            poligono[1].position = {-0.866142f, -0.425197f};
            poligono[2].position = {-0.598425f, -0.0787402f};
            poligono[3].position = {-0.850394f, 0.456693f};
            poligono[4].position = {-0.377953f, 0.929134f};
            poligono[5].position = {-0.0787402f, 0.629921f};
            poligono[6].position = {0.527559f, 0.811024f};
            poligono[7].position = {1.f, 0.204724f};
            poligono[8].position = {0.582677f, -0.212598f};
            poligono[9].position = {0.96063f, -0.448819f};
            poligono[10].position = {0.551181f, -0.866142f};
            poligono[11].position = {-0.362205f, -0.88189f};
    }
    sf::Transform t;
    t.rotate(direccion * (float) (180.0 / PI));
    for (int i = 0; i < poligono.getVertexCount(); i++) {
        poligono[i].color = color;
        poligono[i].position = t.transformPoint(poligono[i].position);
    }

    punto.setPrimitiveType(sf::LineStrip);
    punto.resize(2);
    punto[0].position = {0.0f, 0.0f};
    punto[1].position = {1.0f * limitesPantalla.y / (float) RESOLUCION_BASE.y,
                         1.0f * limitesPantalla.y / (float) RESOLUCION_BASE.y};
    punto[0].color = color;
    punto[1].color = color;
    estado = MOVIMIENTO;
    if (cs != nullptr) {
        switch (tam) {
            case TAM_0:
                sonidoDestruccion = ControladorSonido::EXP_0;
                break;
            case TAM_1:
                sonidoDestruccion = ControladorSonido::EXP_1;
                break;
            case TAM_2:
                sonidoDestruccion = ControladorSonido::EXP_2;
                break;
            default:
                break;
        }
    }
}

//Getters
sf::VertexArray Asteroide::getPuntos() {
    return sf::VertexArray();
}

float Asteroide::getDireccion() {
    return direccion;
}

sf::Vector2f Asteroide::getVelocidad() {
    return velocidad;
}

int Asteroide::getPuntuacion() const {
    switch (tipoTamano) {
        case TAM_0:
            return 100;
        case TAM_1:
            return 50;
        case TAM_2:
            return 20;
        default:
            return 0;
    }
}

void Asteroide::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (estado == MOVIMIENTO) {
        sf::Transform t;
        // El orden en el que se efectuan las transformaciones es importante!
        t.translate(posicion).scale({radio, radio});
        target.draw(poligono, t);
    } else {
        sf::Transform t0, t1, t2, t3, t4, t5, t6, t7;
        t0.translate(posicion0);
        t1.translate(posicion1);
        t2.translate(posicion2);
        t3.translate(posicion3);
        t4.translate(posicion4);
        t5.translate(posicion5);
        t6.translate(posicion6);
        t7.translate(posicion7);

        target.draw(punto, t1);
        target.draw(punto, t2);
        target.draw(punto, t0);
        target.draw(punto, t3);
        target.draw(punto, t4);
        target.draw(punto, t5);
        target.draw(punto, t6);
        target.draw(punto, t7);
    }

}

void Asteroide::mover() {
    switch (estado) {
        case MOVIMIENTO: {
            posicion += velocidad;
            if (posicion.x - 1 >= limites.x) {
                posicion.x -= limites.x;
            } else if (posicion.x + 1 <= 0.0) {
                posicion.x += limites.x;
            }
            if (posicion.y - 1 >= limites.y) {
                posicion.y -= limites.y;
            } else if (posicion.y + 1 <= 0.0) {
                posicion.y += limites.y;
            }
            break;
        }
        case EXPLOSION: {
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
            if ((clock() - start) / (double) CLOCKS_PER_SEC > 2) {
                estado = DESTRUIDO;
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
        default:
            break;
    }
}

void Asteroide::gestionarDestruccion(std::vector<Asteroide> &astds) {
    estado = EXPLOSION;
    recienDestruida = true;
    cs->reproducir(sonidoDestruccion, true);
    switch (tipoTamano) {
        case TAM_0:
            break;
        case TAM_1:
            astds.push_back(Asteroide(posicion, anguloAleatorio(),
                                      {velocidad.x + valorAleatorio(0, ((float) PI / 2) * ratio(limites)),
                                       velocidad.y + valorAleatorio(0, (float) (PI / 2) * ratio(limites))},
                                      (Tipo) enteroAleatorio((int) TIPO_0, (int) TIPO_2), TAM_0, limites, color, cs));
            astds.push_back(Asteroide(posicion, anguloAleatorio(),
                                      {velocidad.x - valorAleatorio(0, ((float) PI / 2) * ratio(limites)),
                                       velocidad.y - valorAleatorio(0, (float) (PI / 2) * ratio(limites))},
                                      (Tipo) enteroAleatorio((int) TIPO_0, (int) TIPO_2), TAM_0, limites, color, cs));
            break;
        case TAM_2:
            astds.push_back(Asteroide(posicion, anguloAleatorio(),
                                      {velocidad.x + valorAleatorio(0, ((float) PI / 2) * ratio(limites)),
                                       velocidad.y + valorAleatorio(0, (float) (PI / 2) * ratio(limites))},
                                      (Tipo) enteroAleatorio((int) TIPO_0, (int) TIPO_2), TAM_1, limites, color, cs));
            astds.push_back(Asteroide(posicion, anguloAleatorio(),
                                      {velocidad.x - valorAleatorio(0, ((float) PI / 2) * ratio(limites)),
                                       velocidad.y - valorAleatorio(0, (float) (PI / 2) * ratio(limites))},
                                      (Tipo) enteroAleatorio((int) TIPO_0, (int) TIPO_2), TAM_1, limites, color, cs));
            break;
    }
}

void Asteroide::cambiarEstado(int nuevoEstado) {
    // De momento no se usa
}
