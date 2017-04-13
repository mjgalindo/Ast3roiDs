#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"

using namespace std;

bool continua = true;

//sf::RenderWindow ventana;
sf::Vector2u resolucion = {800, 600};
vector<vector<double>> poblacion(8);
double mejorTiempo = 0;
vector<double> mejoresPesos;

// Inicializa una red neuronal nueva
neural::Network red(12, 3, {9,3});
vector<double*> pesos = red.getWeights();


vector<Asteroide> asteroides;

double radioTonto = 15;     //Radio del ovni tonto
double radioInteligente = 3*radioTonto/4;       //Radio del ovni inteligente

//PARAMETROS QUE USARA LA RED
double radio = radioInteligente;        //Radio que empleara la red
int iteraciones = 10;

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

vector<Asteroide *> asteroideMasCercano(sf::Vector2f posicion) {
    double distanciaMenor1 = 99999999.0;
    double distanciaMenor2 = 99999999.0;
    double distanciaMenor3 = 99999999.0;
    double distanciaMenor4 = 99999999.0;
    Asteroide *masCercano1 = 0, *masCercano2 = 0, *masCercano3 = 0, *masCercano4 = 0;;
    vector<Asteroide *> masCercanos;
    for (auto ast = asteroides.begin(); ast != asteroides.end(); ++ast) {
        double distanciatmp = distancia(ast->getPosicion(), posicion);
        if (distanciatmp < distanciaMenor1) {
            distanciaMenor4 = distanciaMenor3;
            masCercano4 = masCercano3;
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciaMenor1;
            masCercano2 = masCercano1;
            distanciaMenor1 = distanciatmp;
            masCercano1 = ast.base();
        } else if(distanciatmp < distanciaMenor2) {
            distanciaMenor4 = distanciaMenor3;
            masCercano4 = masCercano3;
            distanciaMenor3 = distanciaMenor2;
            masCercano3 = masCercano2;
            distanciaMenor2 = distanciatmp;
            masCercano2 = ast.base();
        } else if(distanciatmp < distanciaMenor3) {
            distanciaMenor4 = distanciaMenor3;
            masCercano4 = masCercano3;
            distanciaMenor3 = distanciatmp;
            masCercano3 = ast.base();
        } else if(distanciatmp < distanciaMenor4) {
            distanciaMenor4 = distanciatmp;
            masCercano4 = ast.base();
        }
    }
    masCercanos.push_back(masCercano1);
    masCercanos.push_back(masCercano2);
    masCercanos.push_back(masCercano3);
    masCercanos.push_back(masCercano4);
    return masCercanos;
}

void mutacion() {
    for(unsigned int i = 0; i < poblacion.size(); i++) {
        for(unsigned j = 0; j < poblacion[i].size(); j++) {
            if(valorAleatorio() < 0.05) {
                poblacion[i][j] += valorAleatorio((float) -0.5, (float) 0.5);
            }
        }
    }
}


vector<vector<double>> combinar(vector<vector<double>> aux) {
    while (aux.size() < 6) {
        int aleatorio1 = enteroAleatorio(0,2);
        int aleatorio2 = aleatorio1;
        while(aleatorio2 == aleatorio1) {
            aleatorio2 = enteroAleatorio(0,2);
        }

        vector<double> p1;
        int aleatorio3 = enteroAleatorio(0, aux[aleatorio1].size());
        for (unsigned int j = 0; j < aleatorio3; j++) {
            p1.push_back(aux[aleatorio1][j]);
        }
        for (unsigned int j = aleatorio3; j < aux[aleatorio2].size(); j++) {
            p1.push_back(aux[aleatorio2][j]);
        }
        aux.push_back(p1);
    }
    return aux;
}

vector<vector<double>> completar(vector<vector<double>> aux) {
    while (aux.size() < 8) {
        vector<double> p1;
        for (unsigned int j = 0; j < pesos.size(); j++) {
            p1.push_back(valorAleatorio(-5.0f, 5.0f));
        }
        aux.push_back(p1);
    }
    return aux;
}

void sigGeneracion(double tiempo[8]) {
    vector<vector<double>> aux(0);
    double mayorTiempo[3] = {0.0, 0.0, 0.0};
    int mayoresIndice[3] = {0, 0, 0};
    for(int k = 0; k < 8; k++) {
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
        cout << mayorTiempo[k]/iteraciones << " ";
    }
    cout << mayoresIndice[0] << endl;

    ofstream f_hist_out("history.dat", fstream::app);
    if (f_hist_out.good()) {
        for(int k = 0; k < 3; k++) {
            f_hist_out << mayorTiempo[k] << " ";
        }
        f_hist_out << mayoresIndice[0] << endl;
    }
    f_hist_out.close();

    if(mayorTiempo[0] > mejorTiempo) {
        mejorTiempo = mayorTiempo[0];
        mejoresPesos = aux[0];

        for (unsigned int j = 0; j < mejoresPesos.size(); j++) {
            *pesos[j] = mejoresPesos[j];
        }

        string nombreFichero = "geneticos.nn";
        red.write(nombreFichero);

        ofstream f_pesos_out("savedpoint.dat");
        if (f_pesos_out.good()) {
            f_pesos_out << mejorTiempo << " ";
            for(int o=0 ; o<poblacion.size() ; o++) {
                for (int p = 0; p < pesos.size(); p++) {
                    f_pesos_out << poblacion[o][p] << " ";
                }
            }
        }
        f_pesos_out.close();

        if(mejorTiempo>250){
            continua = false;
        }
    }

    //COMBINAR
    poblacion = completar(combinar(aux));
    mutacion();
}

int main() {
    ifstream f_pesos("savedpoint.dat");
    if(f_pesos.good()){
        cout << "Leido desde fichero" << endl;

        f_pesos >> mejorTiempo;

        for(int o=0 ; o<poblacion.size() ; o++) {
            for (int p = 0; p < pesos.size(); p++) {
                double peso;
                f_pesos >> peso;
                poblacion[o].push_back(peso);
            }
        }
    }
    else{
        for(unsigned int i = 0; i < 8; i++) {
            for(unsigned int j = 0; j < pesos.size(); j++) {
                poblacion[i].push_back(valorAleatorio(-5.0f,5.0f));
            }
        }
    }
    f_pesos.close();



    srand((unsigned long) time(NULL));
    //sf::ContextSettings settings;
    //settings.antialiasingLevel = 4;
    //ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Default, settings);
    sf::Vector2f posicionAnterior;
    //ventana.setFramerateLimit(60);
    sf::Clock reloj;
    sf::CircleShape sustitutoOvni(radio);
    sustitutoOvni.setFillColor({200, 10, 10});
    sustitutoOvni.setOrigin(sustitutoOvni.getRadius(), sustitutoOvni.getRadius());
    sustitutoOvni.setPosition({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f});

    // Opcionalmente la lee desde fichero
    // (descomentando las dos lineas siguientes y poniendo el nombre correcto)
    //string inputRed = "entrenado.nn";
    //red = red.read(inputRed);
    unsigned int numAsteroides = 10;
    Asteroide::nuevosAsteroidesAleatorios(asteroides, numAsteroides, resolucion, sf::Color::White,NULL);
    int reinicios = 1;
    int choque = 0;
    reloj.restart();
    double tiempo_aux[8];
    while (continua) {
        tiempo_aux[0] = tiempo_aux[1] = tiempo_aux[2] = tiempo_aux[3] = tiempo_aux[4] = tiempo_aux[5] = tiempo_aux[6] = tiempo_aux[7] = 0;
        for(unsigned int i = 0; i < poblacion.size(); i++) {
            for (unsigned int j = 0; j < pesos.size(); j++) {
                *pesos[j] = poblacion[i][j];
            }
            reloj.restart();
            choque = 0;
            while (choque < iteraciones) {
                /*sf::Event event;
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
                                for (unsigned int j = 0; j < pesos.size(); j++) {
                                    *pesos[j] = mejoresPesos[j];
                                }
                                red.write(nombreFichero);
                            }
                            break;
                        default:
                            break;
                    }
                }
                ventana.clear(sf::Color::Black);*/

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
                double angulo = output2Radians(salida);
                float vMax = 3.0f;
                // Niega el eje Y porque está invertido (valores de Y mayores dan posiciones mas abajo)
                sustitutoOvni.move({vMax * (float) cos(angulo), vMax * (float) -sin(angulo)});
                posicionAnterior = posicionOvni;
                posicionOvni = sustitutoOvni.getPosition();

                tiempo_aux[i] += 1.0/60.0;

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
                    //ventana.draw(*ast);
                    if (distanciaEuclidea(ast->getPosicion(), posicionOvni) <
                        ast->getRadio() + sustitutoOvni.getRadius()) {
                        // Hay colision, se informa a la red y se reinicia la escena aleatoriamente

                        Asteroide::nuevosAsteroidesAleatorios(asteroides, numAsteroides, resolucion, sf::Color::White,
                                                              NULL);
                        sustitutoOvni.setPosition({valorAleatorio(0, resolucion.x), valorAleatorio(0, resolucion.y)});
                        choque++;
                        // cout << reinicios << " " << reloj.getElapsedTime().asSeconds() << '\n';
                        reinicios++;
                        break;
                    }
                }
                //ventana.draw(sustitutoOvni);
                //ventana.display();
            }
        }

        sigGeneracion(tiempo_aux);
    }
}