#ifndef AST3ROIDS_ASTEROIDE_HPP
#define AST3ROIDS_ASTEROIDE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Asteroide {

    private:
        float direccion;
        float size;
        int version;
        sf::Vector2f puntos[12];
        sf::Vector2f posicion;
        sf::Vector2f velocidad;

    public:
        Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, int version, float size);
        ~Asteroide();


        sf::Vector2f* getPuntos();
        float getDireccion();
        sf::Vector2f getPosicion();
        sf::Vector2f getVelocidad();
        void explotar();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


#endif //AST3ROIDS_ASTEROIDE_HPP