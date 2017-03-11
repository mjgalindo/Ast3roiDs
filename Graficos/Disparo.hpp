#ifndef AST3ROIDS_DISPARO_HPP
#define AST3ROIDS_DISPARO_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Asteroide.hpp"

#define PI 3.14159265358979323846

class Nave;
class Ovni;

class Disparo : public sf::Drawable {
    private:
        //Tamano del disparo en pixeles
        static constexpr float TAMANO = 2.0;
        //Distancia maxima a la que llega un disparo
        static constexpr float ALCANCE = 600.0;
        //Velocidad del disparo (total)
        static constexpr float VELOCIDAD = 21.0;

        //Orden: superior, inferior
        sf::VertexArray poligono;
        //Direccion del disparo
        float direccion;
        //Posicion del disparo
        sf::Vector2f posicion;
        //Distancia recorrida
        float distancia;

        sf::Clock reloj;

    public:
        //Constructor
        Disparo();
        Disparo(sf::Vector2f pos_inicial);

        //Destructor
        ~Disparo();

        //Setters
        void setPuntos(sf::Vector2f ps[2]);
        void setDireccion(float dir);
        void setPosicion(sf::Vector2f pos);

        //Getters
        sf::VertexArray* getPuntos();
        float getDireccion();
        sf::Vector2f getPosicion();

        //Dibujo
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Otros
        void mover(sf::Vector2u limites);
        bool comprobarAlcance();
        bool comprobarColision(Asteroide& a);
        bool comprobarColision(Nave& n);
        bool comprobarColision(Ovni& o);
};

#endif //AST3ROIDS_DISPARO_HPP
