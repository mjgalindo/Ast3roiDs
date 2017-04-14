#include "Asteroide3D.hpp"
#include "../matematicas.hpp"

Asteroide3D::Asteroide3D(vj::Shader* shader, vj::Textura* textura) : Elemento3D(shader, textura) {
    fich_obj = "Recursos/Modelos/asteroide.obj";
    cargaMalla();
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
