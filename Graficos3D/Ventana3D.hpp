#ifndef AST3ROIDS_VENTANA3D_HPP
#define AST3ROIDS_VENTANA3D_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Ventana3D : public sf::RenderWindow {
public:
    Ventana3D(sf::VideoMode videoMode, std::string title, unsigned int style, sf::ContextSettings settings,
              unsigned int framerateLimit);

    void clear(sf::Vector3f color);
};

#endif //AST3ROIDS_VENTANA3D_HPP
