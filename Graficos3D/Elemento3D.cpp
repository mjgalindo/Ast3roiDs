#include "Elemento3D.hpp"

using namespace std;

void Elemento3D::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    glBindVertexArray(modelo3D.vertexArrayObject);
    glDrawElements(GL_TRIANGLES, modelo3D.numTriangulos, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void Elemento3D::predibujado(Camara &camara) const {
    shader->bind();
    textura->bind();
    shader->actualizar(pos, camara);
}

void Elemento3D::dibujar(sf::RenderTarget &target, Camara &camara, bool rellenado, sf::RenderStates states) const {
    if (rellenado) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    predibujado(camara);
    draw(target, states);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Elemento3D::destruir() {

}
