#ifndef AST3ROIDS_NAVE_HPP
#define AST3ROIDS_NAVE_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

class Nave : public sf::Drawable {
    //Velocidad de giro
    static const float V_ANGULAR = 5;
    //Numero maximo de disparos activos
    static const float MAX_DISPAROS = 4;

    private:
        //Orden: morro, izquierda, derecha
        sf::Vector2f puntos[3];
        //Direccion de la nave
        float direccion;
        //Posicion de la nave
        sf::Vector2f posicion;
        //Velocidad de la nave
        sf::Vector2f velocidad;
        //Numero de disparos
        int disparos;

    public:
        //Constructor
        Nave();

        //Destructor
        ~Nave();

        //Setters
        void setPuntos(Vector3f ps[3]);
        void setDireccion(float dir);
        void setPosicion(sf::Vector2f pos);
        void setVelocidad(sf::Vector2f vel);

        //Getters
        sf::Vector2f* getPuntos();
        float getDireccion();
        sf::Vector2f getPosicion();
        sf::Vector2f getVelocidad();

        //Otros
        void disparar();
        void recuperarDisparos();
        void rotarIzda();
        void rotarDcha();
        void mover();
        void acelerar();
};

#endif //AST3ROIDS_NAVE_HPP
