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
    posicion = {0, 0, 0};
    escala = {0.1f, 0.1f, 0.1f};
    color = {1.f, 1.f, 1.f};
}

void Nave3D::mover() {
    posicion += velocidad;
}
