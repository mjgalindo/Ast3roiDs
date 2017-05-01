
#ifndef AST3ROIDS_FUEGO_H
#define AST3ROIDS_FUEGO_H

#include <SFML/Graphics/Drawable.hpp>
#include "Elemento3D.hpp"

class Fuego : public Elemento3D {
public:
    Fuego();
    void actualizar(Posicionamiento p);
    void dibujar(sf::RenderTarget &target, Camara &camara, bool rellenar, sf::RenderStates states) const;

};


#endif //AST3ROIDS_FUEGO_H
