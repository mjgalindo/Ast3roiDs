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
}

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, glm::vec3 pos, glm::vec3 vel, glm::vec3 rot,
                         glm::vec3 esc) :
        csonido(controladorSonido),
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
    int aleatorio = enteroAleatorio(0, 20);

    if (aleatorio < 2) {
        asteroides.push_back(
                Asteroide3D(csonido, this->pos.posicion,
                            {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                             velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                             velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                            this->pos.rotacion,
                            {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0, this->pos.escala.z / 2.0}));
    } else if (aleatorio < 14) {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

    } else if (aleatorio < 18) {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));
    } else {
        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));

        asteroides.push_back(Asteroide3D(csonido, this->pos.posicion,
                                         {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                          velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                         this->pos.rotacion,
                                         {this->pos.escala.x / 2.0, this->pos.escala.y / 2.0,
                                          this->pos.escala.z / 2.0}));
    }
}
