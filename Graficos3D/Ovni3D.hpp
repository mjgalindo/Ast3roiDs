#ifndef AST3ROIDS_OVNI3D_HPP
#define AST3ROIDS_OVNI3D_HPP


#include <SFML/Graphics/Drawable.hpp>
#include "../Colisiones.hpp"
#include "Elemento3D.hpp"
#include "Asteroide3D.hpp"
#include "Disparo3D.hpp"
#include "Nave3D.hpp"

class Ovni3D : public Elemento3D {
public:
    Ovni3D(ControladorSonido *controladorSonido, float limitesMovimiento);

    void actualizar(std::vector<Asteroide3D> asteroides, Nave3D nave);
    void dibujar(sf::RenderTarget &target, Camara &camara, sf::RenderStates states = sf::RenderStates::Default) const;

    void disparar();

    const float VELOCIDAD_INICIAL = 5.0f;
    glm::vec3 velocidad;
    glm::vec3 direccion;

private:
    std::vector<Disparo3D> disparos;
    float limiteMovimiento;
    ControladorSonido *csonido;

};


#endif //AST3ROIDS_OVNI3D_HPP
