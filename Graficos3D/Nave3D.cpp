#include <string>
#include "Nave3D.hpp"
#include "../matematicas.hpp"

using namespace std;
using namespace sf;

Nave3D::Nave3D(vj::Shader *shader, vj::Textura *textura) : Elemento3D(shader, textura) {
    fich_obj = "Recursos/Modelos/nave.obj";
    cargaMalla();
    velocidad = {
            valorAleatorio(0.0f, VELOCIDAD_MAX),
            valorAleatorio(0.0f, VELOCIDAD_MAX),
            valorAleatorio(0.0f, VELOCIDAD_MAX)
    };
    pos.posicion = {0.0f, 0.0f, 0.0f};
    pos.escala = {0.5f, 0.5f, 0.5f};
    pos.rotacion = {0.0f, 0.0f, 0.0f};
}

void Nave3D::mover() {
    // TODO: Implementar de verdad
    pos.posicion += velocidad * (1.0f / 60.0f);
}
