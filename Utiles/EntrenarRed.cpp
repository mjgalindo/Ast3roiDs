#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"
#include "../matematicas.hpp"

using namespace std;

sf::RenderWindow ventana;
sf::Vector2u resolucion = {800, 600};
vector<float> direcciones = {PI * 3 / 4,PI,-PI * 3 / 4,PI / 2,PI / 4,0,-PI / 4,-PI / 2};

vector<Asteroide> asteroides;

double ultimaDireccion;
double radioTonto = 15;     //Radio del ovni tonto
double radioInteligente = 3*radioTonto/4;       //Radio del ovni inteligente

//PARAMETROS QUE USARA LA RED
double radio = radioInteligente;        //Radio que empleara la red
double ratioAprendizaje = 0.3;      //Ratio de aprendizaje de la red

// Inicializa una red neuronal nueva
neural::Network red(12, 3, {18,6});

bool leer = true;           //Inicializar red del un fichero
string fichero = "perceptron.nnet";     //Fichero a leer/escribir.

double direccionSegura(sf::CircleShape ovni, sf::Vector2f posicionSegura, std::vector<Asteroide> v) {
    float vMax = 3.0;
    float radioPeligro = 60.0f;
    for (unsigned long long i = 0; i < direcciones.size(); i++) {
        ovni.setPosition(posicionSegura);
        bool choque = false;
        float distanciaRecorrida = 0.0f;
        while (distanciaRecorrida < radioPeligro && !choque) {
            //MOVER OVNI Y COMPROBAR QUE CHOCA
            ovni.move({vMax * (float) cos(direcciones.at(i)) * ratio(resolucion),
                       vMax * (float) sin(direcciones.at(i) * ratio(resolucion))});
            sf::Vector2f posicionOvni = ovni.getPosition();
            // Evita los limites del espacio
            if (posicionOvni.x + 1 <= 0.0) {
                posicionOvni.x += resolucion.x;
            } else if (posicionOvni.x - 1 >= resolucion.x) {
                posicionOvni.x -= resolucion.x;
            }

            if (posicionOvni.y + 1 <= 0, 0) {
                posicionOvni.y += resolucion.y;
            } else if (posicionOvni.y - 1 >= resolucion.y) {
                posicionOvni.y -= resolucion.y;
            }
            ovni.setPosition(posicionOvni);
            for (auto ast = v.begin(); ast != v.end(); ++ast) {
                if (colisionCirculos(posicionOvni, ovni.getRadius(), ast->getPosicion(), ast->getRadio())) {
                    // Hay colision, se informa a la red y se reinicia la escena aleatoriamente
                    choque = true;
                    break;
                }
            }
            distanciaRecorrida += vMax;
        }
        if (!choque) {
            ultimaDireccion = direcciones[i] + valorAleatorio(-PI, PI);
            return ultimaDireccion;
        }
    }
    return ultimaDireccion;
}

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

double output2Radians(vector<double> output) {
    vector<int> salidaEntero;
    for(int i = 0; i < output.size(); i++) {
        if(output.at(i) >= 0) {
            salidaEntero.push_back(1);
        } else {
            salidaEntero.push_back(0);
        }
    }
    switch(salidaEntero.at(0)) {
        case 0:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return 0.0;
                        case 1:
                            return -PI/4;
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return -PI/2;
                        case 1:
                            return -3*PI/4;
                    }
            }
        case 1:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return PI;
                        case 1:
                            return PI/4;
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            return PI/2;
                        case 1:
                            return 3*PI/4;
                    }
            }
    }
}

vector<double> radians2Output(double dir) {
    if(dir == 0.0) {
        return {-1, -1, -1};
    } else if(dir == -PI/4) {
        return {-1, -1, 1};
    } else if(dir == -PI/2) {
        return {-1, 1, -1};
    } else if(dir == -3*PI/4) {
        return {-1, 1, 1};
    } else if(dir == PI) {
        return {1, -1, -1};
    } else if(dir == PI/4) {
        return {1, -1, 1};
    } else if(dir == PI/2) {
        return {1, 1, -1};
    } else if(dir == 3*PI/4) {
        return {1, 1, 1};
    } else {
        return {-1, -1, -1};
    }
}

int main() {
// Inicializa una red neuronal nueva

    srand((unsigned long) time(NULL));
    sf::ContextSettings settings;
    //settings.antialiasingLevel = 4;
    ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Default, settings);
    sf::Vector2f posicionAnterior;
    //ventana.setFramerateLimit(60);
    //sf::Clock reloj;
    sf::CircleShape sustitutoOvni(radio);
    sustitutoOvni.setFillColor({200, 10, 10});
    sustitutoOvni.setOrigin(sustitutoOvni.getRadius(), sustitutoOvni.getRadius());
    sustitutoOvni.setPosition({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f});


    if(leer) {
        red = red.read(fichero);
    }

    ultimaDireccion = 0.0;
    bool continua = true;

    unsigned int numAsteroides = 12;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numAsteroides, resolucion, sf::Color::White,NULL);
    double tiempo = 0.0;
    int reinicios = 1;
    unsigned int iteraciones = 0;
    while (continua) {
        iteraciones++;
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
                        if(red.write(fichero)) {
                            cout << "Fichero " << fichero << " escrito con exito" << endl;
                        } else {
                            cout << "Error al escribir el fichero " << fichero << endl;
                        }
                    }
                    break;
                default:
                    break;
            }
        }

        //ventana.clear(sf::Color::Black);

        sf::Vector2f posicionOvni = sustitutoOvni.getPosition();
        vector<Asteroide *> asteroidePeligroso = asteroideMasCercano(posicionOvni);
        vector<double> entradasRed{asteroidePeligroso[0]->getPosicion().x - posicionOvni.x,
                                   asteroidePeligroso[0]->getPosicion().y - posicionOvni.y,
                                   asteroidePeligroso[0]->getVelocidad().x,
                                   asteroidePeligroso[0]->getVelocidad().y,
                                   asteroidePeligroso[1]->getPosicion().x - posicionOvni.x,
                                   asteroidePeligroso[1]->getPosicion().y - posicionOvni.y,
                                   asteroidePeligroso[1]->getVelocidad().x,
                                   asteroidePeligroso[1]->getVelocidad().y,
                                   asteroidePeligroso[2]->getPosicion().x - posicionOvni.x,
                                   asteroidePeligroso[2]->getPosicion().y - posicionOvni.y,
                                   asteroidePeligroso[2]->getVelocidad().x,
                                   asteroidePeligroso[2]->getVelocidad().y};

        vector<double> salida = red.run(entradasRed);
        double salidaSegura = direccionSegura(sustitutoOvni,posicionAnterior,asteroides);
        double angulo = output2Radians(salida);
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
        bool choque = false;
        for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
            ast->mover();
          //  ventana.draw(*ast);
            if (distanciaEuclidea(ast->getPosicion(), posicionOvni) < ast->getRadio() + sustitutoOvni.getRadius()) {
                // Hay colision, se informa a la red y se reinicia la escena aleatoriamente
                choque = true;
                break;
            }
        }
        if (choque) {
            red.trainSingle(entradasRed, radians2Output(salidaSegura), ratioAprendizaje);
            Asteroide::nuevosAsteroidesAleatorios(asteroides, numAsteroides, resolucion,sf::Color::White,NULL);
            sustitutoOvni.setPosition({valorAleatorio(0, resolucion.x), valorAleatorio(0, resolucion.y)});
            cout << reinicios << " " << tiempo << '\n';
            reinicios++;
            iteraciones = 0;
            tiempo = 0.0;
        } else {
            tiempo = tiempo + 1.0/60.0;
        }
       /* ventana.draw(sustitutoOvni);
        ventana.display();*/
    }
}

