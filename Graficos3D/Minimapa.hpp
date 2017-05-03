#ifndef AST3ROIDS_MINIMAPA_HPP
#define AST3ROIDS_MINIMAPA_HPP

#include <SFML/Graphics.hpp>
#include "Nave3D.hpp"
#include "Ovni3D.hpp"
#include "Asteroide3D.hpp"
#include "../Estados.hpp"

class Minimapa : public sf::Drawable{

    private:

        sf::Vector2f posicion;
        sf::Vector2u dimensiones;
        bool ejeX, ejeY, ejeZ;

        bool elementosSet;
        Nave3D* nave;
        Ovni3D* ovni;
        std::vector<Asteroide3D>* asteroides;

        float radio;

    public:

        // 2 de los 3 ejes deben ser true y el otro false;
        Minimapa(sf::Vector2f pos, sf::Vector2u dimensiones, bool ejeX, bool ejeY, bool ejeZ);

        void setElementos3D(Nave3D* n, Ovni3D* o, std::vector<Asteroide3D>* va, float radio);

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};


#endif //AST3ROIDS_MINIMAPA_HPP
