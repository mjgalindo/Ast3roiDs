#ifndef AST3ROIDS_MOVIL_HPP
#define AST3ROIDS_MOVIL_HPP

class Movil : public sf::Sprite {
    private:
        Vector2f velocidad;

    public:
        //Constructores
        Movil();
        Movil(Vector2f posicion, Vector2f vel);
        Movil(Vector2f posicion, Vector2f vel, sf::Texture textura);
        Movil(float posX, float posY, float velX, float velY);
        Movil(float posX, float posY, float velX, float velY, sf::Texture textura);

        //Destructor
        ~Movil();

        //Getters
        Vector2f getVelocidad();

        //Setters
        void setVelocidad(Vector2f vel);
        void setVelocidad(float velX, float velY);

        //Otros
        void acelerar(Vector2f a);
        void acelerar(float ax, float ay);
        void mover();
};

#endif //AST3ROIDS_MOVIL_HPP
