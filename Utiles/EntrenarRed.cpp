#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"

using namespace std;

sf::RenderWindow ventana;
sf::Vector2u MAX_SIZE = {800, 600};

vector<Asteroide> asteroides;

void aleatorizaAsteroides(unsigned int numAsteroides) {
    vector<Tipo> tipos = {TIPO_0, TIPO_1, TIPO_2};
    vector<Tamano> tamanos = {TAM_0, TAM_1, TAM_2};
    asteroides.clear();
    for (int i = 0; i < numAsteroides; ++i) {
        asteroides.push_back(Asteroide({rand() % MAX_SIZE.x*1.0f, rand() % MAX_SIZE.y*1.0f}, 0.4,
                                       {(rand() % 50 / 50.0f) * 2, (rand() % 50 / 50.0f) * 2},
                                       TIPO_1, tamanos.at((unsigned int) (rand() % 3))));
    }
}

Asteroide *asteroideMasCercano(sf::Vector2f posicion) {
    double distanciaMenor = 99999999.0;
    Asteroide *masCercano = 0;
    for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
        double distanciatmp = (posicion.x - ast->getPosicion().x) * (posicion.x - ast->getPosicion().x) +
                              (posicion.y - ast->getPosicion().y) * (posicion.y - ast->getPosicion().y);
        if (distanciatmp < distanciaMenor) {
            distanciaMenor = distanciatmp;
            masCercano = ast.base();
        }
    }
    return masCercano;
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    ventana.create(sf::VideoMode(MAX_SIZE.x, MAX_SIZE.y), "Ast3roiDs", sf::Style::Default, settings);

    ventana.setFramerateLimit(60);
    ventana.setKeyRepeatEnabled(false);
    ventana.setVerticalSyncEnabled(true);

    sf::Clock reloj;
    sf::CircleShape sustitutoOvni(15);
    sustitutoOvni.setFillColor({200,10,10});
    sustitutoOvni.setPosition({rand() % MAX_SIZE.x * 1.0f, rand() % MAX_SIZE.y * 1.0f});
    bool continua = true;

    // Inicializa una red neuronal nueva
    neural::Network red(6, 1, {20});
    aleatorizaAsteroides(5);
    while (continua) {
        sf::Event event;
        if (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    continua = false;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        ventana.close();
                        continua = false;
                    }
                    break;
                default:
                    break;
            }
        }

        ventana.clear(sf::Color::Black);

        ventana.draw(sustitutoOvni);
        sf::Vector2f posicionOvni = sustitutoOvni.getPosition();
        Asteroide *asteroidePeligroso = asteroideMasCercano(
                {posicionOvni.x + sustitutoOvni.getRadius(), posicionOvni.y + sustitutoOvni.getRadius()});
        vector<double> entradasRed{posicionOvni.x, posicionOvni.y, asteroidePeligroso->getPosicion().x,
                                   asteroidePeligroso->getPosicion().y, asteroidePeligroso->getVelocidad().x,
                                   asteroidePeligroso->getVelocidad().y};

        double salida = (red.run(entradasRed)[0] + 1) / 2.0;

        if (salida < 1 * (1.0 / 8.0)) {
            sustitutoOvni.move({0, 1});
        } else if (salida < 2 * (1.0 / 8.0)) {
            sustitutoOvni.move({1, 1});
        } else if (salida < 3 * (1.0 / 8.0)) {
            sustitutoOvni.move({1, 0});
        } else if (salida < 4 * (1.0 / 8.0)) {
            sustitutoOvni.move({1, -1});
        } else if (salida < 5 * (1.0 / 8.0)) {
            sustitutoOvni.move({0, -1});
        } else if (salida < 6 * (1.0 / 8.0)) {
            sustitutoOvni.move({-1, -1});
        } else if (salida < 7 * (1.0 / 8.0)) {
            sustitutoOvni.move({-1, 0});
        } else if (salida < 8 * (1.0 / 8.0)) {
            sustitutoOvni.move({-1, -1});
        }

        posicionOvni = sustitutoOvni.getPosition();

        if (posicionOvni.x < 0) {
            posicionOvni.x = MAX_SIZE.x;
            sustitutoOvni.setPosition(posicionOvni);
        } else if (posicionOvni.x > MAX_SIZE.x) {
            posicionOvni.x = 0;
            sustitutoOvni.setPosition(posicionOvni);
        }

        if (posicionOvni.y < 0) {
            posicionOvni.y = MAX_SIZE.y;
            sustitutoOvni.setPosition(posicionOvni);
        } else if (posicionOvni.y > MAX_SIZE.y) {
            posicionOvni.y = 0;
            sustitutoOvni.setPosition(posicionOvni);
        }

        posicionOvni.x += sustitutoOvni.getRadius();
        posicionOvni.y += sustitutoOvni.getRadius();

        cout << salida << ' ' << posicionOvni.x << ' ' << posicionOvni.y << '\n';

        for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
            ast->mover(MAX_SIZE);
            ventana.draw(*ast);
            if ((posicionOvni.x - ast->getPosicion().x) * (posicionOvni.x - ast->getPosicion().x) +
                (posicionOvni.y - ast->getPosicion().y) * (posicionOvni.y - ast->getPosicion().y) <
                ast->getRadio() * ast->getRadio() + sustitutoOvni.getRadius() * sustitutoOvni.getRadius()) {
                // Hay colision, se informa a la red y se reinicia la escena aleatoriamente

            }
        }
        ventana.display();
    }
}


