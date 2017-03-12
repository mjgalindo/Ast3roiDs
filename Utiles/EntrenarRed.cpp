#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"

using namespace std;

sf::RenderWindow ventana;
sf::Vector2u MAX_SIZE = {800, 600};

vector<Asteroide> asteroides;

inline float distanciaEuclidea(sf::Vector2f a, sf::Vector2f b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void aleatorizaAsteroides(unsigned int numAsteroides) {
    vector<Tipo> tipos = {TIPO_0, TIPO_1, TIPO_2};
    vector<Tamano> tamanos = {TAM_0, TAM_1, TAM_2};
    asteroides.clear();
    float vMax = 5;
    for (int i = 0; i < numAsteroides; ++i) {
        asteroides.push_back(Asteroide({rand() % MAX_SIZE.x * 1.0f, rand() % MAX_SIZE.y * 1.0f}, 0.4,
                                       {vMax * ((rand() % 50 - 25) / 25.0f), vMax * ((rand() % 50 - 25) / 25.0f)},
                                       TIPO_1, tamanos.at((unsigned int) (rand() % 3))));
    }
}

Asteroide *asteroideMasCercano(sf::Vector2f posicion) {
    double distanciaMenor = 99999999.0;
    Asteroide *masCercano = 0;
    for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
        double distanciatmp = distanciaEuclidea(ast->getPosicion(), posicion);
        if (distanciatmp < distanciaMenor) {
            distanciaMenor = distanciatmp;
            masCercano = ast.base();
        }
    }
    return masCercano;
}

int main() {
    srand((unsigned long) time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    ventana.create(sf::VideoMode(MAX_SIZE.x, MAX_SIZE.y), "Ast3roiDs", sf::Style::Default, settings);

    ventana.setFramerateLimit(60);
    ventana.setKeyRepeatEnabled(false);
    ventana.setVerticalSyncEnabled(true);

    sf::Clock reloj;
    sf::CircleShape sustitutoOvni(15);
    sustitutoOvni.setFillColor({200, 10, 10});
    sustitutoOvni.setOrigin(sustitutoOvni.getRadius(), sustitutoOvni.getRadius());
    sustitutoOvni.setPosition({rand() % MAX_SIZE.x * 1.0f, rand() % MAX_SIZE.y * 1.0f});

    bool continua = true;

    // Inicializa una red neuronal nueva
    neural::Network red(6, 1, {20});
    aleatorizaAsteroides(10);
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
        Asteroide *asteroidePeligroso = asteroideMasCercano(posicionOvni);
        vector<double> entradasRed{posicionOvni.x, posicionOvni.y, asteroidePeligroso->getPosicion().x,
                                   asteroidePeligroso->getPosicion().y, asteroidePeligroso->getVelocidad().x,
                                   asteroidePeligroso->getVelocidad().y};

        double salida = (red.run(entradasRed)[0] + 1) / 2.0;
        double angulo = 0;
        if (salida < 1 * (1.0 / 8.0)) {
            angulo = PI / 2;
            cout << "U ";
        } else if (salida < 2 * (1.0 / 8.0)) {
            angulo = PI / 4;
            cout << "UR ";
        } else if (salida < 3 * (1.0 / 8.0)) {
            angulo = 0;
            cout << "R ";
        } else if (salida < 4 * (1.0 / 8.0)) {
            angulo = -PI / 4;
            cout << "DR ";
        } else if (salida < 5 * (1.0 / 8.0)) {
            angulo = -PI / 2;
            cout << "D ";
        } else if (salida < 6 * (1.0 / 8.0)) {
            angulo = -PI * 3 / 4;
            cout << "DL ";
        } else if (salida < 7 * (1.0 / 8.0)) {
            angulo = PI;
            cout << "L ";
        } else if (salida < 8 * (1.0 / 8.0)) {
            angulo = PI * 3 / 4;
            cout << "UL ";
        }
        float vMax = 3.0f;
        // Niega el eje Y porque está invertido (valores de Y mayores dan posiciones mas abajo)
        sustitutoOvni.move({vMax * (float) cos(angulo), vMax * (float) -sin(angulo)});

        posicionOvni = sustitutoOvni.getPosition();

        // Evita los limites del espacio
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

        cout << salida << ' ' << posicionOvni.x << ' ' << posicionOvni.y << '\n';

        for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
            ast->mover(MAX_SIZE);
            ventana.draw(*ast);
            if (distanciaEuclidea(ast->getPosicion(), posicionOvni) < ast->getRadio() + sustitutoOvni.getRadius()) {
                // Hay colision, se informa a la red y se reinicia la escena aleatoriamente

            }
        }
        ventana.draw(sustitutoOvni);

        ventana.display();
    }
}


