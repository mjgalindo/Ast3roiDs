#include <tiny_obj_loader.h>
#include <iostream>
#include <fstream>
#include "ControladorModelos.hpp"

using namespace std;

static std::array<std::string, ControladorModelos::NUM_MODELOS> ficheros{
        "Recursos/Modelos/asteroide.obj",
        "Recursos/Modelos/nave2.obj",
        "Recursos/Modelos/disparo.obj",
        "Recursos/Modelos/esfera2.obj",
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

static unsigned int parseaObj(string fichero, vector<int>& indices,
                     vector<float>& vertices, vector<float>& normales, vector<float>& texturas){
    ifstream fich(fichero);
    if (!fich.is_open()) throw invalid_argument("Fichero: " + fichero + " no encontrado o no disponible.");

    unsigned int numTriangulos = 0;

    vector<float> t_vertices, t_normales, t_texturas;

    indices.clear();
    vertices.clear();
    normales.clear();
    texturas.clear();

    string tipoLinea;
    array<int, 9> ids;
    float x, y, z;
    int indiceActual = 1;

    while (fich.good()){
        fich >> tipoLinea;
        if (tipoLinea == "v") {
            fich >> x >> y >> z;
            t_vertices.push_back(x);
            t_vertices.push_back(y);
            t_vertices.push_back(z);
        }
        else if (tipoLinea == "vn") {
            fich >> x >> y >> z;
            t_normales.push_back(x);
            t_normales.push_back(y);
            t_normales.push_back(z);
        }
        else if (tipoLinea == "vt") {
            fich >> x >> y;
            t_texturas.push_back(x);
            t_texturas.push_back(y);
        }
        else if (tipoLinea == "f"){
            numTriangulos++;
            for (int i = 0; i < ids.size(); ++i){
                fich >> ids[i];
                fich.get();
            }
            for (int i = 0; i < 3; i++){
                vertices.push_back(t_vertices[ids[i*3] * 3]);
                vertices.push_back(t_vertices[ids[i*3] * 3+1]);
                vertices.push_back(t_vertices[ids[i*3] * 3+2]);

                texturas.push_back(t_texturas[ids[i*3+1] * 2]);
                texturas.push_back(t_texturas[ids[i*3+1] * 2+1]);

                normales.push_back(t_normales[ids[i*3+2] * 3]);
                normales.push_back(t_normales[ids[i*3+2] * 3+1]);
                normales.push_back(t_normales[ids[i*3+2] * 3+2]);

                indices.push_back(indiceActual++);
            }
        }
    }

    return numTriangulos;
}

void ControladorModelos::cargaMalla(TipoModelo tipo) {
    vector<int> indices;
    vector<float> vertices, normales, ctextura;

    modelos[tipo].numTriangulos = parseaObj(ficheros[tipo], indices, vertices, normales, ctextura);

    glGenVertexArrays(1, &modelos[tipo].vertexArrayObject);
    glBindVertexArray(modelos[tipo].vertexArrayObject);

    glGenBuffers(Modelo::NUM_BUFFERS, modelos[tipo].vertexArrayBuffers);

    glBindBuffer(GL_ARRAY_BUFFER, modelos[tipo].vertexArrayBuffers[Modelo::POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0],
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
    //std::cout << ficheros[(int)tipo] << '\n';
    //for (int i = 0; i < ctextura.size(); i+=2){
    //    std::cout << ctextura[i] << ' '  << ctextura[i+1] << '\n';
    //}
    //std::cout << "\n\n\n\n";
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
