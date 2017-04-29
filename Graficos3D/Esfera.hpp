#ifndef AST3ROIDS_ESFERA_HPP
#define AST3ROIDS_ESFERA_HPP

#include "Elemento3D.hpp"
#include "../Util3D/ControladorTexturas.hpp"
#include "../Util3D/ControladorShaders.hpp"

class Esfera : public Elemento3D {
public:
    Esfera(ControladorTexturas::TipoTextura textura, ControladorShaders::TipoShader shader, glm::vec3 posicion = glm::vec3{0, 0, 0},
           glm::vec3 escala = glm::vec3{1, 1, 1}, bool verSoloMalla = false);

};

#endif //AST3ROIDS_ESFERA_HPP
