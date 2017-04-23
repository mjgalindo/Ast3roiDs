#include "Esfera.hpp"
#include "../Util3D/ControladorShaders.hpp"

Esfera::Esfera(ControladorTexturas::TipoTextura textura, glm::vec3 posicion, glm::vec3 escala, bool verSoloMalla) :
        Elemento3D(ControladorShaders::getShader(ControladorShaders::BRILLO),
                   ControladorTexturas::getTextura(textura)) {
    modelo3D = ControladorModelos::getModelo(ControladorModelos::ESFERA);
    pos.posicion = posicion;
    pos.escala = escala;
    modoMalla = verSoloMalla;
}

void Esfera::dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states) const {
    if (modoMalla) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Muestra sollo la malla sin rellenar triangulos
    Elemento3D::dibujar(target, camara, states);
    if (modoMalla) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

