
#ifndef AST3ROIDS_OVNIINTELIGENTE_HPP
#define AST3ROIDS_OVNIINTELIGENTE_HPP

#include "Ovni.hpp"

class OvniInteligente : public Ovni {
    private:
        float error = PI/2;
    public:

        OvniInteligente(sf::Vector2u limitesPantalla, sf::Color color);

        ~OvniInteligente();

        void disparar(sf::Vector2f nave);

        virtual int getPuntuacion() const;

        void mover(std::vector<Asteroide> &v, Triangular &n);

        void disminuirError();
};


#endif //AST3ROIDS_OVNIINTELIGENTE_H