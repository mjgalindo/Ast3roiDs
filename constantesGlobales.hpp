#ifndef AST3ROIDS_CONSTANTESGLOBALES_HPP
#define AST3ROIDS_CONSTANTESGLOBALES_HPP

#include <SFML/System.hpp>
#include <vector>

static sf::Vector2u RESOLUCION_BASE = {800, 600};

static std::vector<sf::Vector2u> resolucionesValidas() {
    std::vector<sf::VideoMode> resolucionesAceptadas = sf::VideoMode::getFullscreenModes();
    std::vector<sf::Vector2u> validas;
    for (auto resIt = resolucionesAceptadas.end() - 1; resIt >= resolucionesAceptadas.begin(); --resIt) {
        if (resIt->height / (float) resIt->width == RESOLUCION_BASE.y / (float) RESOLUCION_BASE.x)
            validas.push_back({resIt->width, resIt->height});
    }
    return validas;
}

static float ratio(sf::Vector2u resolucion1, sf::Vector2u resolucion2 = RESOLUCION_BASE) {
    return resolucion1.y / (float) resolucion2.y;
}

#endif //AST3ROIDS_CONSTANTESGLOBALES_HPP
