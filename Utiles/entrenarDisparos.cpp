#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"

using namespace std;

bool continua = true;

//sf::RenderWindow ventana;
sf::Vector2u resolucion = {800, 600};

// Inicializa una red neuronal nueva
neural::Network red(2, 1, {4});



struct Configuracion {
    sf::Vector2u resolucion;
    bool pantallaCompleta;
    unsigned int volumen;
    unsigned int antialiasing;
    int colorId;
    array<sf::Color, 4u> COLORES = {sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue};

    sf::Keyboard::Key girar_izquierda = sf::Keyboard::Left;
    sf::Keyboard::Key girar_derecha = sf::Keyboard::Right;
    sf::Keyboard::Key acelerar = sf::Keyboard::A;
    sf::Keyboard::Key disparar = sf::Keyboard::D;
    sf::Keyboard::Key hiperespacio = sf::Keyboard::Space;

    Configuracion() {
        resolucion = RESOLUCION_BASE;
        pantallaCompleta = false;
        volumen = 50;
        antialiasing = 2;
        colorId = 0;

        girar_izquierda = sf::Keyboard::Left;
        girar_derecha = sf::Keyboard::Right;
        acelerar = sf::Keyboard::A;
        disparar = sf::Keyboard::D;
        hiperespacio = sf::Keyboard::Space;
    }

    sf::Color color() {
        return COLORES[colorId];
    }

    string colorString() {
        switch (colorId) {
            case 0:
                return "BLANCO";
            case 1:
                return "ROJO";
            case 2:
                return "VERDE";
            case 3:
                return "AZUL";
            default:
                return "???";
        }
    }
};


/*
void sigGeneracion(long int distancia[8]) {


    if(mayorDistancia[0] > mejorDistancia) {
        mejorDistancia = mayorDistancia[0];
        mejoresPesos = aux[0];

        for (unsigned int j = 0; j < mejoresPesos.size(); j++) {
            *pesos[j] = mejoresPesos[j];
        }

        string nombreFichero = "entrenando.nn";
        red.write(nombreFichero);

        ofstream f_pesos_out("savedpoint.dat");
        if (f_pesos_out.good()) {
            f_pesos_out << mejorDistancia << " ";
            for(int o=0 ; o<poblacion.size() ; o++) {
                for (int p = 0; p < pesos.size(); p++) {
                    f_pesos_out << poblacion[o][p] << " ";
                }
            }
        }
        f_pesos_out.close();

        if(mejorDistancia>250000){
            continua = false;
        }
    }
}*/

int main() {
    /*ifstream f_pesos("savedpoint.dat");
    if (f_pesos.good()) {
        cout << "Leido desde fichero" << endl;

        f_pesos >> mejorDistancia;

        for (int o = 0; o < poblacion.size(); o++) {
            for (int p = 0; p < pesos.size(); p++) {
                double peso;
                f_pesos >> peso;
                poblacion[o].push_back(peso);
            }
        }
    } else {
        for (unsigned int i = 0; i < 8; i++) {
            for (unsigned int j = 0; j < pesos.size(); j++) {
                poblacion[i].push_back(valorAleatorio(-1.0f, 1.0f));
            }
        }
    }
    f_pesos.close();*/


    srand((unsigned long) time(NULL));
    //sf::ContextSettings settings;
    //settings.antialiasingLevel = 4;
    //ventana.create(sf::VideoMode(resolucion.x, resolucion.y), "Ast3roiDs", sf::Style::Default, settings);
    sf::Vector2f posicionAnterior;
    //ventana.setFramerateLimit(60);
    sf::Clock reloj;
    sf::CircleShape sustitutoOvni(15);
    sustitutoOvni.setFillColor({200, 10, 10});
    sustitutoOvni.setOrigin(sustitutoOvni.getRadius(), sustitutoOvni.getRadius());
    sustitutoOvni.setPosition({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f});
    long puntuacion = 0;
    ControladorSonido csonido;
    Configuracion configuracionGlobal;
    Nave nave({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f},resolucion,&puntuacion,
              configuracionGlobal.color(), &csonido);

    // Opcionalmente la lee desde fichero
    // (descomentando las dos lineas siguientes y poniendo el nombre correcto)
    //string inputRed = "entrenado.nn";
    //red = red.read(inputRed);
    int disparos = 1;
    int aciertos = 0;
    reloj.restart();
    while (continua) {
        /*distancia_aux[0] = distancia_aux[1] = distancia_aux[2] = distancia_aux[3] = distancia_aux[4] = distancia_aux[5] = distancia_aux[6] = distancia_aux[7] = 0;

        reloj.restart();
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

        vector<double> entradasRed{nave.getPosicion().x-sustitutoOvni.getPosition().x,
                                   nave.getPosicion().y-sustitutoOvni.getPosition().y
                                            };

        double salida = red.run(entradasRed)[0]*PI;
        Disparo disparo(sustitutoOvni.getPosition(),salida,resolucion,sf::Color::White);
        disparo.setDireccion((float)salida);
        bool acertado = false;
        while(!acertado && disparo.comprobarAlcance()) {
            disparo.mover();
            if(disparo.comprobarColision(nave)) {
                acertado = true;
            }
        }
        if(!acertado) {
            sf::Vector2f vectorDir = (nave.getPosicion() - sustitutoOvni.getPosition());
            double direccionDisp = atan2(vectorDir.y, vectorDir.x)/PI;
            red.trainSingle(entradasRed,{direccionDisp},0.3);
           cout << aciertos << " " << disparos << " Fallo" << endl;
        } else {
            aciertos++;
            cout << aciertos << " " << disparos << " Acierto" << endl;
            disparos = 0;
        }
        sustitutoOvni.setPosition({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f});
        nave.setPosicion({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f});
        disparos++;
    }

    cout << "Reinicios: " << aciertos << " tiempo: " << reloj.getElapsedTime().asSeconds() << endl;
}