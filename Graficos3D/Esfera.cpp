#include "Esfera.hpp"

Esfera::Esfera(ControladorTexturas::TipoTextura textura, ControladorShaders::TipoShader shader, glm::vec3 posicion, glm::vec3 escala, bool verSoloMalla) :
        Elemento3D(ControladorShaders::getShader(shader),
                   ControladorTexturas::getTextura(textura)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::ESFERA);
    pos.posicion = posicion;
    pos.escala = escala;
}
