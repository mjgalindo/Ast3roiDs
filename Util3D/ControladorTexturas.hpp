#ifndef AST3ROIDS_CONTROLADORTEXTURAS_HPP
#define AST3ROIDS_CONTROLADORTEXTURAS_HPP
#include "Textura.hpp"

class ControladorTexturas {
public:
    ControladorTexturas();

    enum TipoTextura {
        BLANCO = 0,
        OVNI,
        NAVE,
        ESPACIO,
        MULTI,
        ROCA,
        FUEGO,
        NUM_TEXTURAS
    };

    static vj::Textura* getTextura(TipoTextura tipo);

};

#endif //AST3ROIDS_CONTROLADORTEXTURAS_HPP
