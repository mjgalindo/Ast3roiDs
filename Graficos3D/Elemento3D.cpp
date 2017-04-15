#include <tiny_obj_loader.h>
#include "Elemento3D.hpp"

using namespace std;

void Elemento3D::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Muestra sollo la malla sin rellenar triangulos
    glBindVertexArray(modelo3D.vertexArrayObject);
    glDrawElements(GL_TRIANGLES, modelo3D.numTriangulos, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

Elemento3D &Elemento3D::predibujado(Camara &camara) {
    shader->bind();
    textura->bind();
    shader->actualizar(pos, camara);
    return *this;
}