#ifndef AST3ROIDS_TRIANGULAR_HPP
#define AST3ROIDS_TRIANGULAR_HPP

#include <SFML/Graphics.hpp>

class Triangular {

    public:

        sf::VertexArray vs;
        sf::Vector2f posicion;
        float direccion;
        float tamano;

        int estado;

        //Constructores
        Triangular();
        Triangular(sf::Vector2f p, float d, float t);

        //Destructor
        ~Triangular();

        //Setters
        void setPosicion(sf::Vector2f p);
        void setDireccion(float d);
        void setTamano(float t);
        void setVertices(sf::VertexArray t);

        //Getters
        sf::Vector2f getPosicion();
        float getDireccion();
        float getTamano();
        int getEstado();
        sf::VertexArray getVertices();
        sf::VertexArray getTriangulo();

        //Otros
        virtual void cambiarEstado(int nuevoEstado)=0;
};

#endif //AST3ROIDS_TRIANGULAR_HPP
