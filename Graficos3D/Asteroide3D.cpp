#include "Asteroide3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento) : csonido(controladorSonido),
                                                                                          Elemento3D(ControladorShaders::getShader(
                                                                         ControladorShaders::SIMPLE),
                                                                            ControladorTexturas::getTextura(
                                                                                    ControladorTexturas::BLANCO)) {

    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = {
            valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX),
            valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX),
            valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX)
    };

    velocidadAngular = glm::angleAxis(
            valorAleatorio(0.0f, 0.2f),
            glm::normalize(glm::vec3{
                    valorAleatorio((float) 0, (float) 1),
                    valorAleatorio((float) 0, (float) 1),
                    valorAleatorio((float) 0, (float) 1)})
    );
    velocidadAngular = glm::normalize(velocidadAngular);

    pos.posicion = {
            valorAleatorio(0.8f * -limitesMovimiento, 0.8f * limitesMovimiento),
            valorAleatorio(0.8f * -limitesMovimiento, 0.8f * limitesMovimiento),
            valorAleatorio(0.8f * -limitesMovimiento, 0.8f * limitesMovimiento),
    };
    float escala = valorAleatorio(0.5f, 2.0f);
    pos.escala = {escala, escala, escala};
    pos.rotacion = glm::angleAxis((float) PI, glm::vec3{1, 0, 0});

    version = TIPO3D_0;
    tamano3D = TAM3D_2;
    limiteMovimiento = limitesMovimiento;
}

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento, glm::vec3 pos, glm::vec3 vel,
                         glm::vec3 rot,
                         Tipo3D tipo, Tamano3D tam3D) :
        csonido(controladorSonido),
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = vel;
    this->pos.posicion = pos;
    this->pos.rotacion = rot;

    version = tipo;
    tamano3D = tam3D;

    switch (version) {
        case TIPO3D_0:
        case TIPO3D_1:
        case TIPO3D_2:
        default:
            modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    }

    switch (tamano3D) {
        case TAM3D_0:
            this->pos.escala = {0.5f, 0.5f, 0.5f};
            break;
        case TAM3D_1:
            this->pos.escala = {1.0f, 1.0f, 1.0f};
            break;
        case TAM3D_2:
            this->pos.escala = {2.0f, 2.0f, 2.0f};
            break;
    }
    limiteMovimiento = limitesMovimiento;
}

void Asteroide3D::actualizar() {
    //pos.rotacion = glm::quat(glm::toMat4(velocidadAngular) * glm::toMat4(pos.rotacion));
    pos.posicion += velocidad;
    if (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
        pos.posicion = glm::vec3{0, 0, 0} - pos.posicion;
        while (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
            pos.posicion.x = (abs(pos.posicion.x) - 0.1f) * pos.posicion.x / abs(pos.posicion.x);
            pos.posicion.y = (abs(pos.posicion.y) - 0.1f) * pos.posicion.y / abs(pos.posicion.y);
            pos.posicion.z = (abs(pos.posicion.z) - 0.1f) * pos.posicion.z / abs(pos.posicion.z);
        }
    }
}

void Asteroide3D::colisionDetectada(std::vector<Asteroide3D> &asteroides) {
    int aleatorio = enteroAleatorio(0, 20);
    switch (tamano3D) {
        case TAM3D_0:
            csonido->reproducir(ControladorSonido::EXP_0, true);
            break;
        case TAM3D_1:
            csonido->reproducir(ControladorSonido::EXP_1, true);
            if (aleatorio < 2) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));

            } else if (aleatorio < 14) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
            } else if (aleatorio < 18) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
            } else {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
            }
            break;
        case TAM3D_2:
            csonido->reproducir(ControladorSonido::EXP_2, true);
            if (aleatorio < 2) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            } else if (aleatorio < 14) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            } else if (aleatorio < 18) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            } else {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.y + valorAleatorio(-(float) (PI / 2), (float) (PI / 2)),
                                                  velocidad.z + valorAleatorio(-(float) (PI / 2), (float) (PI / 2))},
                                                 {anguloAleatorio(), anguloAleatorio(), anguloAleatorio()},
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            }
            break;
    }
}
