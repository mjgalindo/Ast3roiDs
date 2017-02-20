#ifndef AST3ROIDS_NAVE_HPP
#define AST3ROIDS_NAVE_HPP

enum Estado { OK, ACELERANDO, DESTRUIDA, RECONSTRUYENDO };

class Nave : public sf::Movil {
    private:
        float velocidadAngular;

        int vidas;
        long int puntuacion;

        Estado estado;

        sf::Texture naveAcelerando;
        sf::Texture naveDestruida;
        sf::Texture naveReconstruyendo;

    public:
        //Constructores
        Nave();
        Nave(Vector2f posicion, Vector2f vel, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK);
        Nave(Vector2f posicion, Vector2f vel, sf::Texture t, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK);
        Nave(float posX, float posY, float velX, float velY, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK);
        Nave(float posX, float posY, float velX, float velY, sf::Texture t, float velAng=1.0, int vidas=3, long int puntuacion=0, Estado e=OK);

        //Destructor
        ~Nave();

        //Getters
        float getVelocidadAngular();
        int getVidas();
        long int getPuntuacion();
        Estado getEstado();
        const sf::Texture* getTxtAcelerando();
        const sf::Texture* getTxtDestruida();
        const sf::Texture* getTxtReconstruyendo();

        //Setters
        void setVelocidadAngular(float va);
        void setVidas(int v);
        void setPuntuacion(long int punt);
        void setEstado(Estado est);
        void setTxtAcelerando(sf::Texture t);
        void setTxtDestruida(sf::Texture t);
        void setTxtReconstruyendo(sf::Texture t);

        //Otros
        void destruir();
        void reconstruir();
        void aumentarPuntuacion(int puntos);
        void disparar();
        void girar();
        void saltar();
};

#endif //AST3ROIDS_NAVE_HPP
