#ifndef AST3ROIDS_MALLA_HPP
#define AST3ROIDS_MALLA_HPP

#include <string>
#include <tiny_obj_loader.h>
#include <SFML/Graphics.hpp>

class Malla : public sf::Drawable {
public:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    // Valores del modelo actual
    sf::Vector3f posicion;
    sf::Vector3f rotacion;
    sf::Vector3f escala;
    sf::Vector3f color;

    // Estructuras contenedoras del modelo 3D
    tinyobj::attrib_t atrib;
    std::vector<tinyobj::shape_t> figuras;
    std::vector<tinyobj::material_t> materiales;

    std::string fich_obj;
    const std::string ruta_obj = "Recursos/Modelos";

    void cargaMalla();
};


#endif //AST3ROIDS_MALLA_HPP
