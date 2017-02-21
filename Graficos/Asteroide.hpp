#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <SFML/Graphics.hpp>

class Asteroide {

    private:
        std::vector<sf::Vector2f> puntos;
        sf::Vector2f posicion;
        float velocidad;
        float direccion;

    public:
        Asteroide(float, float);
        void explotar();
        void movimiento();
};


#endif //AST3ROIDS_ASTEROIDE_HPP