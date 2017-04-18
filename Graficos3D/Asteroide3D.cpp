#include "Asteroide3D.hpp"
#include "../matematicas.hpp"
#include "../Util3D/ControladorTexturas.hpp"

Asteroide3D::Asteroide3D(vj::Shader *shader) :
        Elemento3D(shader, ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
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

void Asteroide3D::mover() {
    pos.posicion += velocidad * (1 / 60.f);
}
