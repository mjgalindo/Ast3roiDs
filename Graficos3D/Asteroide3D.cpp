#include "Asteroide3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"
#include <glm/gtx/intersect.hpp>

static constexpr std::array<float, 4> ESCALAS = {2.0f, 6.0f, 9.0f, 0.2f};

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento, Tamano3D tam3D) :
        csonido(controladorSonido), Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                                               ControladorTexturas::getTextura(ControladorTexturas::ROCA)) {

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

    pos.escala = {ESCALAS[tam3D], ESCALAS[tam3D], ESCALAS[tam3D]};
    pos.rotacion = glm::angleAxis((float) PI, glm::vec3{1, 0, 0});

    version = TIPO3D_0;
    tamano3D = tam3D;
    limiteMovimiento = limitesMovimiento;
}

Asteroide3D::Asteroide3D(ControladorSonido *controladorSonido, float limitesMovimiento, glm::vec3 posicion,
                         glm::vec3 vel,
                         glm::quat rot,
                         Tipo3D tipo, Tamano3D tam3D) :
        csonido(controladorSonido),
        Elemento3D(ControladorShaders::getShader(ControladorShaders::SIMPLE),
                   ControladorTexturas::getTextura(ControladorTexturas::ROCA)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = vel;
    pos.posicion = posicion;
    pos.rotacion = rot;

    version = tipo;
    tamano3D = tam3D;

    switch (version) {
        case TIPO3D_0:
        case TIPO3D_1:
        case TIPO3D_2:
        default:
            modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    }

    pos.escala = {ESCALAS[tam3D], ESCALAS[tam3D], ESCALAS[tam3D]};

    limiteMovimiento = limitesMovimiento;
}

void Asteroide3D::actualizar() {
    if (estado == EXPLOTANDO) {
        for (int i = 0; i < NUM_FRAGMENTOS; i++) {
            fragmentosExplosion[i].actualizar();
        }
        if (reloj.getElapsedTime().asSeconds() >= TIEMPO_EXPLOSION) {
            estado = DESTRUIDO;
        }
    }

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

void Asteroide3D::colisionDetectada(int nivel, std::vector<Asteroide3D> &asteroides) {
    if (estado != Elemento3D::NORMAL) return;
    estado = EXPLOTANDO;
    reloj.restart();
    for (int i = 0; i < NUM_FRAGMENTOS; i++) {
        fragmentosExplosion.emplace_back(nullptr, limiteMovimiento, TAM3D_FRAGMENTO);
        fragmentosExplosion[i].pos.posicion = pos.posicion;
    }

    int aleatorio = enteroAleatorio(0, 20);
    switch (tamano3D) {
        case TAM3D_FRAGMENTO:
            // No debería suceder
            break;
        case TAM3D_0:
            csonido->reproducir(ControladorSonido::EXP_0, true);
            break;
        case TAM3D_1:
            csonido->reproducir(ControladorSonido::EXP_1, true);
            if (aleatorio < 2) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));

            } else if (aleatorio < 14) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
            } else if (aleatorio < 18) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
            } else {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_0));
            }
            break;
        case TAM3D_2:
            csonido->reproducir(ControladorSonido::EXP_2, true);
            if (aleatorio < 2) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            } else if (aleatorio < 14) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            } else if (aleatorio < 18) {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            } else {
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
                asteroides.push_back(Asteroide3D(csonido, limiteMovimiento, this->pos.posicion,
                                                 {velocidad.x + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.y + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f)),
                                                  velocidad.z + valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX * (1.0f+(float)nivel/20.0f))},
                                                 rotacionAleatoria(),
                                                 (Tipo3D) enteroAleatorio(0, 2), TAM3D_1));
            }
            break;
    }
}

void Asteroide3D::dibujarSiCercaAntipoda(glm::vec3 puntoCercano, float distancia, sf::RenderTarget &target,
                                         Camara &camara, sf::RenderStates states) {

    if (distanciaEuclidea(pos.posicion, puntoCercano) < distancia) return;

    glm::vec3 dirColisionEsfera = glm::normalize(puntoCercano - glm::vec3{0, 0, 0});
    glm::vec3 puntoInterseccion, normal;
    glm::intersectRaySphere(puntoCercano, dirColisionEsfera,
                            glm::vec3{0, 0, 0}, limiteMovimiento, puntoInterseccion, normal);
    glm::vec3 antipoda = glm::vec3{0, 0, 0} - puntoInterseccion;
    if (distanciaEuclidea(pos.posicion, antipoda) < distancia) {

        glm::vec3 posicionReal = pos.posicion;
        pos.posicion = puntoCercano + (pos.posicion - antipoda);

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Muestra sollo la malla sin rellenar triangulos
        dibujar(target, camara, false, states);
        pos.posicion = posicionReal;
    }
}

void Asteroide3D::dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar, sf::RenderStates states) const {
    if (estado == EXPLOTANDO) {
        for (int i = 0; i < NUM_FRAGMENTOS; i++) {
            fragmentosExplosion[i].dibujar(target, camara, rellenar, states);
        }
    } else {
        Elemento3D::dibujar(target, camara, rellenar, states);
    }
}
