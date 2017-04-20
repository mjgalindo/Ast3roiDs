
#ifndef AST3ROIDS_OVNIINTELIGENTE_HPP
#define AST3ROIDS_OVNIINTELIGENTE_HPP

#include "Ovni.hpp"

class OvniInteligente : public Ovni {
private:
    float error = (float) (PI / 4);
    std::string ficheroRed = "disparo.nnet";

    vector<double> contexto;
    int ocultas = 0;
    shared_ptr<neural::Layer> capaOculta;     //Capa oculta de la red

public:

    OvniInteligente(sf::Vector2u limitesPantalla, sf::Color color, ControladorSonido *cs);

    ~OvniInteligente();

    void disparar(sf::Vector2f nave);

    virtual int getPuntuacion() const;

    double output2RadiansDisparo(std::vector<double> output);

    double output2RadiansMover(std::vector<double> output);

    std::vector<Asteroide *> asteroideMasCercano(sf::Vector2f posicion, std::vector<Asteroide> asteroides);

    void mover(std::vector<Asteroide> &astds, Triangular &nave);

    void disminuirError();

    double direccionSegura(sf::CircleShape ovni, sf::Vector2f posicionSegura, std::vector<Asteroide> v);
};


#endif //AST3ROIDS_OVNIINTELIGENTE_H