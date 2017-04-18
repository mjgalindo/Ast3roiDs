#include <string>
#include "Nave3D.hpp"
#include "../matematicas.hpp"
#include "../Util3D/ControladorTexturas.hpp"

using namespace std;
using namespace sf;

Nave3D::Nave3D(vj::Shader *shader) :
        Elemento3D(shader, ControladorTexturas::getTextura(ControladorTexturas::NAVE)) {

    modelo3D = ControladorModelos::getModelo(ControladorModelos::TipoModelo::NAVE);
    velocidad = {0.0f, 0.0f, 0.0f};
    pos.posicion = {0.0f, 0.0f, 0.0f};
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = {0.0f, -PI / 2, 0.0f};
}

void Nave3D::actualizar() {
    // Gira la nave
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        pos.rotacion.y += 0.01f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        pos.rotacion.y -= 0.01f;

    direccion = matrizRotacion(pos.rotacion) * glm::vec4(1.0, 0.0f, 0.0f, 0.0f);
    direccion = glm::normalize(direccion);

    // Acelera
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        velocidad += direccion / 60.0f;
    else velocidad = velocidad * 0.98f;

    pos.posicion += velocidad * (1 / 60.f);
}
