#include "Asteroide3D.hpp"
#include "../matematicas.hpp"

Asteroide3D::Asteroide3D() {
    fich_obj = "Recursos/Modelos/asteroide.obj";
    cargaMalla();
    velocidad = {
            valorAleatorio(0.0f, VELOCIDAD_MAX),
            valorAleatorio(0.0f, VELOCIDAD_MAX),
            valorAleatorio(0.0f, VELOCIDAD_MAX)
    };
    posicion = {0, 0, 0};
    escala = {0.1f, 0.1f, 0.1f};
    color = {0.f, 1.f, 1.f};
}

void Asteroide3D::mover() {
    posicion += velocidad * (1 / 60.f);
}
