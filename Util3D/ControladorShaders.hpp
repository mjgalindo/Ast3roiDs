#ifndef AST3ROIDS_CONTROLADORSHADERS_HPP
#define AST3ROIDS_CONTROLADORSHADERS_HPP
#include "Shader.hpp"

class ControladorShaders {
public:
    ControladorShaders();

    enum TipoShader {
        SIMPLE = 0,
        BRILLO,
        NUM_SHADERS
    };

    static vj::Shader* getShader(TipoShader tipo);
};

#endif //AST3ROIDS_CONTROLADORSHADERS_HPP
