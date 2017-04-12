#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "Camara.hpp"

struct Transformacion {
    Transformacion(const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot = glm::vec3(),
                   const glm::vec3 &escala = glm::vec3(1.0f, 1.0f, 1.0f))
            : posicion(pos), rotacion(rot), escala(escala) {}

    inline glm::mat4 matrizModelo() const {
        glm::mat4 posMat = glm::translate(posicion);
        glm::mat4 scaleMat = glm::scale(escala);
        glm::mat4 rotX = glm::rotate(rotacion.x, glm::vec3(1.0, 0.0, 0.0));
        glm::mat4 rotY = glm::rotate(rotacion.y, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 rotZ = glm::rotate(rotacion.z, glm::vec3(0.0, 0.0, 1.0));
        glm::mat4 rotMat = rotX * rotY * rotZ;

        return posMat * rotMat * scaleMat;
    }

    inline glm::mat4 modeloVistaProyeccion(const Camara &camara) const {
        return camara.proyeccion() * matrizModelo();
    }

    glm::vec3 posicion;
    glm::vec3 rotacion;
    glm::vec3 escala;
};

#endif
