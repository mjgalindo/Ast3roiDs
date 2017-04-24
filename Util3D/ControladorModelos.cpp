#include <tiny_obj_loader.h>
#include "ControladorModelos.hpp"

using namespace std;

static std::array<std::string, ControladorModelos::NUM_MODELOS> ficheros{
        "Recursos/Modelos/asteroide.obj",
        "Recursos/Modelos/nave2.obj",
        "Recursos/Modelos/disparo.obj",
        "Recursos/Modelos/esfera.obj",
        "Recursos/Modelos/ovni.obj"
};

static std::array<Modelo, ControladorModelos::NUM_MODELOS> modelos;

static string ruta_obj = "Recursos/Modelos/";

/**
 * Replica las normales y coordenadas uv definidas en atrib para que haya el mismo numero de normales que de
 * vertices y que se puedan indexar con los mismos valores.
 */
void replica(const tinyobj::attrib_t &atrib, const tinyobj::shape_t &figura, vector<float> &normales,
             vector<float> &ctextura, vector<int> &indices) {
    normales.resize(atrib.vertices.size());
    ctextura.resize(atrib.vertices.size());
    indices.resize(figura.mesh.indices.size());
    for (unsigned int i = 0; i < figura.mesh.indices.size(); i++) {
        normales[figura.mesh.indices[i].vertex_index * 3] = atrib.normals[figura.mesh.indices[i].normal_index * 3];
        normales[figura.mesh.indices[i].vertex_index * 3 + 1] =
                atrib.normals[figura.mesh.indices[i].normal_index * 3 + 1];
        normales[figura.mesh.indices[i].vertex_index * 3 + 2] =
                atrib.normals[figura.mesh.indices[i].normal_index * 3 + 2];
        if (figura.mesh.indices[i].texcoord_index != -1) {
            ctextura[figura.mesh.indices[i].vertex_index * 2] =
                    atrib.texcoords[figura.mesh.indices[i].texcoord_index * 2];
            ctextura[figura.mesh.indices[i].vertex_index * 2 + 1] =
                    atrib.texcoords[figura.mesh.indices[i].texcoord_index * 2 + 1];
        }

        indices[i] = figura.mesh.indices[i].vertex_index;
    }
}

void ControladorModelos::cargaMalla(TipoModelo tipo) {
    tinyobj::attrib_t atrib;
    std::vector<tinyobj::shape_t> figuras;
    std::vector<tinyobj::material_t> materiales;

    std::string err;
    // Carga el fichero .obj de la malla elegida
    bool ret = tinyobj::LoadObj(&atrib, &figuras, &materiales, &err, ficheros[tipo].c_str(), ruta_obj.c_str(), true);
    if (!ret) {
        throw std::invalid_argument(err);
    }
    if (figuras.size() > 1)
        throw invalid_argument("Hay mas de una figura en el fichero.obj y no es posible saber cual cargar.");

    vector<float> normales;
    vector<float> ctextura;
    vector<int> indices;

    replica(atrib, figuras[0], normales, ctextura, indices);

    modelos[tipo].numTriangulos = (unsigned int) figuras[0].mesh.indices.size();

    glGenVertexArrays(1, &modelos[tipo].vertexArrayObject);
    glBindVertexArray(modelos[tipo].vertexArrayObject);

    glGenBuffers(Modelo::NUM_BUFFERS, modelos[tipo].vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, modelos[tipo].vertexArrayBuffers[Modelo::POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, atrib.vertices.size() * sizeof(atrib.vertices[0]), &atrib.vertices[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, modelos[tipo].vertexArrayBuffers[Modelo::TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, ctextura.size() * sizeof(ctextura[0]), &ctextura[0],
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, modelos[tipo].vertexArrayBuffers[Modelo::NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normales[0]) * normales.size(), &normales[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelos[tipo].vertexArrayBuffers[Modelo::INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

ControladorModelos::ControladorModelos() {
    for (int i = 0; i < NUM_MODELOS; i++) {
        cargaMalla((TipoModelo) i);
    }
}

Modelo ControladorModelos::getModelo(ControladorModelos::TipoModelo tipo) {
    return Modelo(modelos[tipo]);
}

ControladorModelos::~ControladorModelos() {
    for (int i = 0; i < NUM_MODELOS; i++) {
        glDeleteBuffers(Modelo::NUM_BUFFERS, modelos[i].vertexArrayBuffers);
        glDeleteVertexArrays(1, &modelos[i].vertexArrayObject);
    }
}
