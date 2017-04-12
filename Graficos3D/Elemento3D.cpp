#include <tiny_obj_loader.h>
#include "Elemento3D.hpp"

using namespace std;

/**
 * Replica las normales definidas en atrib para que haya el mismo numero de normales que de
 * vertices y que se puedan indexar con los mismos valores.
 */
void replicaNormales(const tinyobj::attrib_t &atrib, const tinyobj::shape_t &figuras, vector<float> &normales,
                     vector<int> &indices) {
    normales.resize(atrib.vertices.size());
    indices.resize(atrib.vertices.size());
    for (int i = 0; i < figuras.mesh.indices.size(); i++) {
        normales[figuras.mesh.indices[i].vertex_index * 3] = atrib.normals[figuras.mesh.indices[i].normal_index * 3];
        normales[figuras.mesh.indices[i].vertex_index * 3 + 1] = atrib.normals[
                figuras.mesh.indices[i].normal_index * 3 + 1];
        normales[figuras.mesh.indices[i].vertex_index * 3 + 2] = atrib.normals[
                figuras.mesh.indices[i].normal_index * 3 + 2];
        indices[i] = figuras.mesh.indices[i].vertex_index;
    }
}

// TODO: Descubrir porqué hacer estas variables locales de cargaMalla ocurren problemas al destruir indices o atrib
tinyobj::attrib_t atrib;
std::vector<tinyobj::shape_t> figuras;
std::vector<tinyobj::material_t> materiales;
vector<float> normales;
vector<int> indices;

void Elemento3D::cargaMalla() {
    std::string err;
    // Carga el fichero .obj de la malla elegida
    bool ret = tinyobj::LoadObj(&atrib, &figuras, &materiales, &err, fich_obj.c_str(), ruta_obj.c_str(), true);
    if (!ret) {
        throw std::invalid_argument(err);
    }
    if (figuras.size() > 1)
        throw invalid_argument("Hay mas de una figura en el fichero.obj y no es posible saber cual cargar.");


    replicaNormales(atrib, figuras[0], normales, indices);

    numTriangulos = (unsigned int) figuras[0].mesh.indices.size();

    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, atrib.vertices.size() * sizeof(atrib.vertices[0]), &atrib.vertices[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, atrib.vertices.size() * sizeof(atrib.texcoords[0]), &atrib.texcoords[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normales[0]) * normales.size(), &normales[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    normales.clear();
    indices.clear();
}

Elemento3D::~Elemento3D() {
    glDeleteBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glDeleteVertexArrays(1, &vertexArrayObject);
}

void Elemento3D::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, numTriangulos, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

Elemento3D &Elemento3D::predibujado(Camara &camara) {
    shader->bind();
    textura->bind();
    shader->actualizar(pos, camara);
    return *this;
}