#include "Malla.hpp"
#include <GL/glew.h>

void Malla::cargaMalla() {
    std::string err;
    bool ret = tinyobj::LoadObj(&atrib, &figuras, &materiales, &err, fich_obj.c_str(), ruta_obj.c_str(), true);
    if (!ret) {
        throw std::invalid_argument(err);
    }
}

void Malla::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    glScalef(escala.x, escala.y, escala.z);
    glTranslatef(posicion.x, posicion.y, posicion.z);
    glRotatef(1, rotacion.x, rotacion.y, rotacion.z);

    glBegin(GL_TRIANGLES);

    glColor3f(color.x, color.y, color.z);
    // TODO: Usar vertex array objects?
    for (size_t s = 0; s < figuras.size(); s++) {
        size_t index_offset = 0;

        for (size_t f = 0; f < figuras[s].mesh.num_face_vertices.size(); f++) {
            int fv = figuras[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = figuras[s].mesh.indices[index_offset + v];
                float vx = atrib.vertices[3 * idx.vertex_index + 0];
                float vy = atrib.vertices[3 * idx.vertex_index + 1];
                float vz = atrib.vertices[3 * idx.vertex_index + 2];
                float nx = atrib.normals[3 * idx.normal_index + 0];
                float ny = atrib.normals[3 * idx.normal_index + 1];
                float nz = atrib.normals[3 * idx.normal_index + 2];
                glNormal3f(nx, ny, nz);
                glVertex3f(vx, vy, vz);
                // TODO: Añadir texturas
            }
            index_offset += fv;

            // per-face material
            figuras[s].mesh.material_ids[f];
        }
    }
    glEnd();
    glPopMatrix();

    // TODO: ESTO NO FUNCIONA, HAY QUE APLICARLO A LA "MATRIZ DEL MODELO"
    //glScalef(escala.x, escala.y, escala.z);
    //glTranslatef(posicion.x, posicion.y, posicion.z);
    //glRotatef(1, rotacion.x, rotacion.y, rotacion.z);
    //glPushMatrix();
}
