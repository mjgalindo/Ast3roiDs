#ifndef AST3ROIDS_NAVE_HPP
#define AST3ROIDS_NAVE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "Disparo.hpp"

#define PI 3.14159265358979323846
#define UMBRAL 0.2

class Nave : public sf::Drawable {
    private:
        //Tamano de la nave en pixeles
        static constexpr float TAMANO = 20;
        //Velocidad de giro (radianes por u.t.)
        static constexpr float V_ANGULAR = PI/30;
        //Aceleracion (pixels por u.t.)
        static constexpr float ACELERACION = 1;
        //Deceleracion (porcentaje de velocidad que se conserva)
        static constexpr float DECELERACION = 0.99;
        //Numero maximo de disparos activos
        static const int MAX_DISPAROS = 4;

        //Orden: morro, izquierda, derecha
        sf::Vector2f puntos[3];
        //Direccion de la nave
        float direccion;
        //Posicion de la nave
        sf::Vector2f posicion;
        //Velocidad de la nave
        sf::Vector2f velocidad;

        //Numero de disparos
        int num_disparos;
        //Vector de disparos
        Disparo disparos[MAX_DISPAROS];

    public:
        //Constructor
        Nave(sf::Vector2f posicion_inicial);

        //Destructor
        ~Nave();

        //Setters
        void setPuntos(sf::Vector2f ps[3]);
        void setDireccion(float dir);
        void setPosicion(sf::Vector2f pos);
        void setVelocidad(sf::Vector2f vel);

        //Getters
        sf::Vector2f* getPuntos();
        float getDireccion();
        sf::Vector2f getPosicion();
        sf::Vector2f getVelocidad();

        //Dibujo
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Otros
        void disparar();
        void recuperarDisparo(int d);
        void rotarIzda();
        void rotarDcha();
        void mover(sf::Vector2u limites);
        void acelerar();
        void frenar();
};

#endif //AST3ROIDS_NAVE_HPP
