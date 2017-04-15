#ifndef AST3ROIDS_CONTROLADORTEXTURAS_HPP
#define AST3ROIDS_CONTROLADORTEXTURAS_HPP
#include "Textura.hpp"

class ControladorTexturas {
public:
    ControladorTexturas();

    enum TipoTextura {
        BLANCO = 0,
        NAVE,
        NUM_TEXTURAS
    };

    static vj::Textura* getTextura(TipoTextura tipo);

private:
    static void cargaTextura(TipoTextura tipo);

};

#endif //AST3ROIDS_CONTROLADORTEXTURAS_HPP
