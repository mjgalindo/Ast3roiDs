#include "Asteroide3D.hpp"
#include "../matematicas.hpp"
#include "../Util3D/ControladorTexturas.hpp"

Asteroide3D::Asteroide3D(vj::Shader* shader) :
        Elemento3D(shader, ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ASTEROIDE);
    velocidad = {
            valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX),
            valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX),
            valorAleatorio(-VELOCIDAD_MAX, VELOCIDAD_MAX)
    };
    pos.posicion = {0.0f, 0.0f, 0.0f};
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = {PI, 0.0f, 0.0f};
}

void Asteroide3D::mover() {
    pos.posicion += velocidad * (1 / 60.f);
}
