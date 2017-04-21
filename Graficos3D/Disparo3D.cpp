#include <iostream>
#include "Disparo3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

Disparo3D::Disparo3D(glm::vec3 direccion, glm::vec3 posicion) :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::BRILLO),
                   ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::DISPARO);
    pos.posicion = posicion;
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = {0.0f, 0.0f, 0.0f};
    velocidad = direccion * VELOCIDAD_BASE;
}

void Disparo3D::actualizar() {
    auto tmp = pos.posicion + velocidad;
    pos.posicion = tmp;
    // TODO: Comprobar colisiones con todo lo que se pase como parámetro.
}
