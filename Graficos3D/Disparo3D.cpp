#include <iostream>
#include "Disparo3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

Disparo3D::Disparo3D(glm::vec3 direccion, glm::vec3 posicion, glm::vec3 rotacion) :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::BRILLO),
                   ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::DISPARO);
    pos.posicion = posicion;
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = rotacion;
    velocidad = direccion * VELOCIDAD_BASE;
}

void Disparo3D::actualizar() {
    pos.posicion = pos.posicion + velocidad;
    if (distanciaEuclidea(pos.posicion, posicionInicial) > DISTANCIA_MAX) {
        estado = DESTRUIDO;
        return;
    }
    // TODO: Comprobar colisiones con todo lo que se pase como parámetro.
}
