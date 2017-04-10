#include <string>
#include "Nave3D.hpp"
#include "../matematicas.hpp"

using namespace std;
using namespace sf;

Nave3D::Nave3D() {
    fich_obj = "Recursos/Modelos/nave.obj";
    cargaMalla();
    velocidad = {
            valorAleatorio(0.0f, VELOCIDAD_MAX),
            valorAleatorio(0.0f, VELOCIDAD_MAX),
            valorAleatorio(0.0f, VELOCIDAD_MAX)
    };
    posicion = {0, 0, -5};
    escala = {0.1f, 0.1f, 0.1f};
    rotacion = {1.0f, 0.0f, 0.0f};
    color = {0.8f, 0.8f, 0.9f};
}

void Nave3D::mover() {
    posicion += velocidad * (1.0f / 60.0f);
}
