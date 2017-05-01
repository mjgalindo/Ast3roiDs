#include "ControladorTexturas.hpp"

using namespace std;

static array<unique_ptr<vj::Textura>, ControladorTexturas::NUM_TEXTURAS> texturas;
static array<string, ControladorTexturas::NUM_TEXTURAS> ficheros {
        "Recursos/Texturas/blanco.png",
        "Recursos/Texturas/ovniUV_v1.png",
        "Recursos/Texturas/naveUV_color_V2.png",
        "Recursos/Texturas/espacio2.jpg",
        "Recursos/Texturas/multi.png",
        "Recursos/Texturas/roca.jpg",
        "Recursos/Texturas/fuego_UV.png"
};

ControladorTexturas::ControladorTexturas() {
    for (int i = 0; i < NUM_TEXTURAS; i++){
        texturas[i] = unique_ptr<vj::Textura>(new vj::Textura(ficheros[i]));
    }
}

vj::Textura *ControladorTexturas::getTextura(ControladorTexturas::TipoTextura tipo) {
    return texturas[tipo].get();
}
