#ifndef AST3ROIDS_GRAFICO_HPP
#define AST3ROIDS_GRAFICO_HPP

#include <SFML/Graphics.hpp>

class Grafico{

    private:
        sf::Sprite sprite;
        sf::Texture textura;

    public:
        //Constructores
        Grafico();
        Grafico(sf::Sprite sp);
        Grafico(float x, float y);
        Grafico(sf::Vector2f pos);

        //Destructor
        ~Grafico();

        //Setters
        void setPosicion(sf::Vector2f pos);
        void setPosicion(float x, float y);
        void setX(float x);
        void setY(float y);

        void setSprite(sf::Sprite sp);
        void setTextura(sf::Texture tx);
        bool setTextura(std::string pathTx);

        //Getters
        sf::Vector2f getPosicion();
        float getX();
        float getY();

        sf::Vector2u getTamano();
        unsigned int getAncho();
        unsigned int getAlto();

        sf::Sprite getSprite();
        sf::Texture getTx();

        //Dibujar
        void dibujar(sf::RenderWindow* ventana);
};

#endif