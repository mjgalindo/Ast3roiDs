#include <iostream>
#include "Disparo3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

Disparo3D::Disparo3D(glm::vec3 direccion, glm::vec3 posicion, glm::quat rotacion, float limitesMovimiento) :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::BRILLO),
                   ControladorTexturas::getTextura(ControladorTexturas::BLANCO)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::DISPARO);
    pos.posicion = posicion;
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = rotacion;
    velocidad = direccion * VELOCIDAD_BASE;
    distanciaRestante = DISTANCIA_MAX;
    limiteMovimiento = limitesMovimiento;
    posicionInicial = posicion;
}

void Disparo3D::cambioDisparoEsferico() {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::ESFERA);
    pos.escala = { 0.3f, 0.3f, 0.3f };
}

void Disparo3D::actualizar() {
    pos.posicion = pos.posicion + velocidad;
    if ((pos.posicion.x != pos.posicion.x) | (pos.posicion.y != pos.posicion.y) | (pos.posicion.z != pos.posicion.z)){
        // Pueden suceder errores de coma flotante que causaran que alguno de los valores de posición tenga un valor no
        // válido. En tal caso se destruye el disparo.
        estado = DESTRUIDO;
        return;
    }
    if (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
        distanciaRestante = distanciaRestante - distanciaEuclidea(pos.posicion, posicionInicial);
        posicionInicial = pos.posicion;

        pos.posicion = glm::vec3{0, 0, 0} - pos.posicion;
        while (distanciaEuclidea(pos.posicion, glm::vec3{0, 0, 0}) > limiteMovimiento) {
            pos.posicion.x = (abs(pos.posicion.x) - 0.1f) * pos.posicion.x / abs(pos.posicion.x);
            pos.posicion.y = (abs(pos.posicion.y) - 0.1f) * pos.posicion.y / abs(pos.posicion.y);
            pos.posicion.z = (abs(pos.posicion.z) - 0.1f) * pos.posicion.z / abs(pos.posicion.z);
        }
    }

    if (distanciaEuclidea(pos.posicion, posicionInicial) > distanciaRestante) {
        estado = DESTRUIDO;
    }
}
