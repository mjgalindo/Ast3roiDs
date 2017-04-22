#include "Asteroide3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido) : csonido(controladorSonido),
                                                                 Elemento3D(ControladorShaders::getShader(
                                                                         ControladorShaders::SIMPLE),
                                                                            ControladorTexturas::getTextura(
                                                                                    ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = {0.0f, 0.0f, 0.0f};
    pos.posicion = {
            valorAleatorio(-80, 80),
            valorAleatorio(-80, 80),
            valorAleatorio(-80, 80),
    };
    float escala = valorAleatorio(0.5f, 2.0f);
    pos.escala = {escala, escala, escala};
    pos.rotacion = {PI, 0.0f, 0.0f};

    version = TIPO3D_0;
    tamano3D = TAM3D_2;
}

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, glm::vec3 pos,
                         glm::vec3 vel, glm::vec3 rot, glm::vec3 esc) :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = vel;
    this->pos.posicion = pos;
    this->pos.escala = esc;
    this->pos.rotacion = rot;
}

void Asteroide3D::actualizar() {
    pos.posicion += velocidad * (1 / 60.f);
}

void Asteroide3D::colisionDetectada(std::vector<Asteroide3D> &asteroides) {
    csonido->reproducir(ControladorSonido::EXP_1);
    int aleatorio = enteroAleatorio(0, 20);
    int numAsteroides = 1;
    if (aleatorio < 14) numAsteroides = 2;
    else if (aleatorio < 18) numAsteroides = 3;
    else numAsteroides = 4;
    for (int i = 0; i < numAsteroides; i++) {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion, {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                                              this->pos.escala.z / 2.0}));

    }
}
