#include "ControladorShaders.hpp"

using namespace std;

static array<unique_ptr<vj::Shader>, ControladorShaders::NUM_SHADERS> shaders;
static array<string, ControladorShaders::NUM_SHADERS> ficheros {
        "Recursos/Shaders/shaderBasico",
        "Recursos/Shaders/shaderBrillante"
};

ControladorShaders::ControladorShaders() {
    for (int i = 0; i < NUM_SHADERS; i++){
        shaders[i] = unique_ptr<vj::Shader>(new vj::Shader(ficheros[i]));
    }
}

vj::Shader *ControladorShaders::getShader(ControladorShaders::TipoShader tipo) {
    return shaders[(int) tipo].get();
}
