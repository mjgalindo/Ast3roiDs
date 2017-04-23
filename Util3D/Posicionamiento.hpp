#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Camara.hpp"
#include "../matematicas.hpp"

inline glm::mat4 matrizRotacion(const glm::quat &rotXYZ) {
    return glm::toMat4(rotXYZ);
}

struct Posicionamiento {
    Posicionamiento(const glm::vec3 &pos = glm::vec3(), const glm::quat &rot = glm::angleAxis(0.0f, glm::vec3{1, 0, 0}),
                    const glm::vec3 &escala = glm::vec3(1.0f, 1.0f, 1.0f))
            : posicion(pos), rotacion(rot), escala(escala) {}

    inline glm::mat4 matrizModelo() const {
        glm::mat4 posMat = glm::translate(posicion);
        glm::mat4 scaleMat = glm::scale(escala);
        glm::mat4 rotMat = matrizRotacion(rotacion);

        return posMat * rotMat * scaleMat;
    }

    inline glm::mat4 modeloVistaProyeccion(const Camara &camara) const {
        return camara.proyeccion() * matrizModelo();
    }

    glm::vec3 posicion;
    glm::vec3 escala;
    glm::quat rotacion;
};

#endif
