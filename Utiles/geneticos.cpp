#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"

using namespace std;

sf::RenderWindow ventana;
sf::Vector2u resolucion = {800, 600};
vector<vector<double>> poblacion(6);

// Inicializa una red neuronal nueva
neural::Network red(6, 1, {20,20,20});


vector<Asteroide> asteroides;

double distancia(sf::Vector2f a, sf::Vector2f b) {
    double distanciaX = (a.x - b.x);
    double distanciaY = (a.y - b.y);
    if((resolucion.x + a.x) - b.x < abs(distanciaX)) {
        distanciaX = (resolucion.x + a.x) - b.x;
    }
    if((resolucion.y + a.y) - b.y < abs(distanciaY)) {
        distanciaY = (resolucion.y + a.y) - b.y;
    }
    return sqrt(distanciaX * distanciaX + (distanciaY * distanciaY));
}


vector<Asteroide *> asteroideMasCercano(sf::Vector2f posicion) {
    double distanciaMenor1 = 99999999.0;
    double distanciaMenor2 = 99999999.0;
    double distanciaMenor3 = 99999999.0;
    Asteroide *masCercano1 = 0, *masCercano2 = 0, *masCercano3 = 0;
    vector<Asteroide *> masCercanos;
    for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
        double distanciatmp = distancia(ast->getPosicion(), posicion);
        if (distanciatmp < distanciaMenor1) {
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciaMenor1;
            masCercano2 = masCercano1;
            distanciaMenor1 = distanciatmp;
            masCercano1 = ast.base();
        } else if(distanciatmp < distanciaMenor2) {
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciatmp;
            masCercano2 = ast.base();
        } else if(distanciatmp < distanciaMenor3) {
            distanciaMenor3 = distanciatmp;
            masCercano3 = ast.base();
        }
    }
    masCercanos.push_back(masCercano1);
    masCercanos.push_back(masCercano2);
    masCercanos.push_back(masCercano3);
    return masCercanos;
}

void mutacion() {
    for(unsigned int i = 0; i < poblacion.size(); i++) {
        for(unsigned j = 0; j < poblacion[i].size(); j++) {
            if(valorAleatorio() < 0.01) {
                poblacion[i][j] = valorAleatorio((float)-0.5, (float)0.5);
            }
        }
    }
}


vector<vector<double>> combinar(vector<vector<double>> aux) {
    while(aux.size() < 6) {
        int aleatorio1 = enteroAleatorio(0,2);
        int aleatorio2 = aleatorio1;
        while(aleatorio2 == aleatorio1) {
            aleatorio2 = enteroAleatorio(0,2);
        }

        vector<double> p1;
        for(unsigned int j = 0; j < aux[aleatorio1].size()/2; j++) {
            p1.push_back(aux[aleatorio1][j]);
        }
        for(unsigned long long int j = aux[aleatorio2].size()/2; j < aux[aleatorio2].size(); j++) {
            p1.push_back(aux[aleatorio2][j]);
        }
        aux.push_back(p1);
    }
    return aux;
}

void sigGeneracion(int tiempo[6]) {
    vector<vector<double>> aux(0);
        int mayorTiempo[3] = {0, 0, 0};
        int mayoresIndice[3] = {0, 0, 0};
        for(int k = 0; k < 6; k++) {
            if(tiempo[k] > mayorTiempo[0]) {
                mayorTiempo[2] = mayorTiempo[1];
                mayoresIndice[2] = mayoresIndice[1];
                mayorTiempo[1] = mayorTiempo[0];
                mayoresIndice[1] = mayoresIndice[0];
                mayorTiempo[0] = tiempo[k];
                mayoresIndice[0] = k;

            } else if(tiempo[k] > mayorTiempo[1]) {
                mayorTiempo[2] = mayorTiempo[1];
                mayoresIndice[2] = mayoresIndice[1];
                mayorTiempo[1] = tiempo[k];
                mayoresIndice[1] = k;
            } else if(tiempo[k] > mayorTiempo[2]) {
                mayorTiempo[2] = tiempo[k];
                mayoresIndice[2] = k;
            }
        }
        for(int k = 0; k < 3; k++) {
            aux.push_back(poblacion[mayoresIndice[k]]);
        }

        //COMBINAR
        poblacion = combinar(aux);
        mutacion();
}

int main() {
    vector<double*> pesos = red.getWeights();
    for(unsigned int i = 0; i < 6; i++) {
        for(unsigned int j = 0; j < pesos.size(); j++) {
            poblacion[i].push_back(valorAleatorio((float)-0.5,(float)0.5));
        }
    }

    srand((unsigned long) time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Default, settings);
    sf::Vector2f posicionAnterior;
    //ventana.setFramerateLimit(60);
    sf::Clock reloj;
    sf::CircleShape sustitutoOvni(15);
    sustitutoOvni.setFillColor({200, 10, 10});
    sustitutoOvni.setOrigin(sustitutoOvni.getRadius(), sustitutoOvni.getRadius());
    sustitutoOvni.setPosition({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f});


    bool continua = true;
    // Opcionalmente la lee desde fichero
    // (descomentando las dos lineas siguientes y poniendo el nombre correcto)
    //string inputRed = "entrenado.nn";
    //red = red.read(inputRed);
    unsigned int numAsteroides = 12;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numAsteroides, resolucion, sf::Color::White);
    int reinicios = 1;
    unsigned int iteraciones = 0;
    int choque = 0;
    reloj.restart();
    while (continua) {
        int tiempo[6] = {0, 0, 0, 0, 0,0};
        for(unsigned int i = 0; i < poblacion.size(); i++) {
            for (unsigned int j = 0; j < pesos.size(); j++) {
                *pesos[j] = poblacion[i][j];
            }
            reloj.restart();
            choque = 0;
            while (choque < 5) {
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
                                string nombreFichero = "entrenando.nn";
                                red.write(nombreFichero);
                            }
                            break;
                        default:
                            break;
                    }
                }

                ventana.clear(sf::Color::Black);

                sf::Vector2f posicionOvni = sustitutoOvni.getPosition();
                vector<Asteroide *> asteroidePeligroso = asteroideMasCercano(posicionOvni);
                vector<double> entradasRed{asteroidePeligroso[0]->getPosicion().x - posicionOvni.x,
                                           posicionOvni.y - asteroidePeligroso[0]->getPosicion().y,
                                           asteroidePeligroso[1]->getPosicion().x - posicionOvni.x,
                                           posicionOvni.y - asteroidePeligroso[1]->getPosicion().y,
                                           asteroidePeligroso[2]->getPosicion().x - posicionOvni.x,
                                           posicionOvni.y - asteroidePeligroso[2]->getPosicion().y};

                double salida = red.run(entradasRed)[0];
                double angulo = 0;
                if (salida < -3 * (2.0 / 8.0)) {
                    angulo = PI * 3 / 4;
                    //cout << "UL ";
                } else if (salida < -2 * (2.0 / 8.0)) {
                    angulo = PI;
                    //cout << "L ";
                } else if (salida < -1 * (2.0 / 8.0)) {
                    angulo = -PI * 3 / 4;
                    //cout << "DL ";
                } else if (salida < 0 * (2.0 / 8.0)) {
                    angulo = PI / 2;
                    //cout << "U ";
                } else if (salida < 1 * (2.0 / 8.0)) {
                    angulo = PI / 4;
                    //cout << "UR ";
                } else if (salida < 2 * (2.0 / 8.0)) {
                    angulo = 0;
                    //cout << "R ";
                } else if (salida < 3 * (2.0 / 8.0)) {
                    angulo = -PI / 4;
                    //cout << "DR ";
                } else if (salida < 4 * (2.0 / 8.0)) {
                    angulo = -PI / 2;
                    //cout << "D ";
                }
                float vMax = 3.0f;
                // Niega el eje Y porque está invertido (valores de Y mayores dan posiciones mas abajo)
                sustitutoOvni.move({vMax * (float) cos(angulo), vMax * (float) -sin(angulo)});
                posicionAnterior = posicionOvni;
                posicionOvni = sustitutoOvni.getPosition();

                // Evita los limites del espacio
                if (posicionOvni.x < 0) {
                    posicionOvni.x = resolucion.x;
                    sustitutoOvni.setPosition(posicionOvni);
                } else if (posicionOvni.x > resolucion.x) {
                    posicionOvni.x = 0;
                    sustitutoOvni.setPosition(posicionOvni);
                }

                if (posicionOvni.y < 0) {
                    posicionOvni.y = resolucion.y;
                    sustitutoOvni.setPosition(posicionOvni);
                } else if (posicionOvni.y > resolucion.y) {
                    posicionOvni.y = 0;
                    sustitutoOvni.setPosition(posicionOvni);
                }

                //cout << salida << ' ' << posicionOvni.x << ' ' << posicionOvni.y << '\n';
                for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
                    ast->mover();
                    ventana.draw(*ast);
                    if (distanciaEuclidea(ast->getPosicion(), posicionOvni) <
                        ast->getRadio() + sustitutoOvni.getRadius()) {
                        // Hay colision, se informa a la red y se reinicia la escena aleatoriamente

                        Asteroide::nuevosAsteroidesAleatorios(asteroides, numAsteroides, resolucion, sf::Color::White);
                        sustitutoOvni.setPosition({valorAleatorio(0, resolucion.x), valorAleatorio(0, resolucion.y)});
                        choque++;
                       // cout << reinicios << " " << reloj.getElapsedTime().asSeconds() << '\n';
                        reinicios++;
                        break;
                    }
                }
                ventana.draw(sustitutoOvni);
                ventana.display();
            }
            tiempo[i] = reloj.getElapsedTime().asMilliseconds() / choque;
        }
        for(int k = 0; k < 6; k++) {
            cout << "Iteraciones poblacion " << k << ": " << tiempo[k] << endl;
        }
        sigGeneracion(tiempo);
    }

    cout << "Reinicios: " << reinicios << " tiempo: " << reloj.getElapsedTime().asSeconds() << endl;
}