
#ifndef AST3ROIDS_OVNIINTELIGENTE_HPP
#define AST3ROIDS_OVNIINTELIGENTE_HPP

#include "Ovni.hpp"

class OvniInteligente : public Ovni {
private:
    float error = (float) (PI / 2);
public:

    OvniInteligente(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs);

    ~OvniInteligente();

    void disparar(sf::Vector2f nave);

    virtual int getPuntuacion() const;

    void mover(std::vector<Asteroide> &astds, Triangular &nave);

    void disminuirError();

    double direccionSegura(sf::CircleShape ovni, sf::Vector2f posicionSegura, std::vector<Asteroide> v);
};


#endif //AST3ROIDS_OVNIINTELIGENTE_H