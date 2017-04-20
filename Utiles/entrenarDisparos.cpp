#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos/Nave.hpp"
#include "../neural/include/neural/Network.h"

using namespace std;

double radioTonto = 15;     //Radio del ovni tonto
double radioInteligente = 3*radioTonto/4;       //Radio del ovni inteligente

//PARAMETROS QUE USARA LA RED
double radio = radioInteligente;        //Radio que empleara la red

double ratioAprendizaje = 0.6;      //Ratio de aprendizaje de la red

string fichero = "disparo.nnet";
bool leer = false;

bool continua = true;

sf::RenderWindow ventana;
sf::Vector2u resolucion = {800, 600};

// Inicializa una red neuronal nueva
neural::Network red(2, 5, {16});



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

        string fich = "entrenaDisparo.nn";
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
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 0.0;
                                        case 1:
                                            return -PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -PI/8;

                                        case 1:
                                            return -3*PI/16;
                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -PI/4;

                                        case 1:

                                            return -5*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -3*PI/8;

                                        case 1:
                                            return -7*PI/16;
                                    }
                            }
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -PI/2;

                                        case 1:

                                            return -9*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -10*PI/16;

                                        case 1:
                                            return -11*PI/16;
                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -3*PI/4;

                                        case 1:
                                            return -13*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return -7*PI/8;

                                        case 1:
                                            return -15*PI/16;
                                    }
                            }
                    }
            }
        case 1:
            switch(salidaEntero.at(1)) {
                case 0:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI;
                                        case 1:
                                            return PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI/8;

                                        case 1:
                                            return 3*PI/16;
                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI/4;

                                        case 1:

                                            return 5*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 3*PI/8;

                                        case 1:
                                            return 7*PI/16;
                                    }
                            }
                    }

                case 1:
                    switch(salidaEntero.at(2)) {
                        case 0:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return PI/2;

                                        case 1:

                                            return 9*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 10*PI/16;

                                        case 1:
                                            return 11*PI/16;

                                    }
                            }
                        case 1:
                            switch(salidaEntero.at(3)) {
                                case 0:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 3*PI/4;

                                        case 1:
                                            return 13*PI/16;
                                    }

                                case 1:
                                    switch(salidaEntero.at(4)) {
                                        case 0:
                                            return 7*PI/8;

                                        case 1:
                                            return 15*PI/16;
                                    }
                            }
                    }
            }
    }
}

vector<double> radians2Output(double dir) {
    if(dir <= 0.0 && dir > -PI/16 ) {
        return {-1,-1,-1, -1, -1};
    } else if(dir <= -PI/16 && dir > -PI/8) {
        return {-1,-1,-1, -1, 1};
    } else if(dir <= -PI/8 && dir > -3*PI/16) {
        return {-1,-1,-1, 1, -1};
    } else if(dir <= -3*PI/16 && dir > -PI/4) {
        return {-1,-1,-1, 1, 1};
    } else if(dir <= -PI/4 && dir > -5*PI/16) {
        return {-1,-1,1,-1, -1};
    } else if(dir <= -5*PI/16 && dir > -3*PI/8) {
        return {-1,-1,1, -1, 1};
    } else if(dir <= -3*PI/8 && dir > -7*PI/16) {
        return {-1,-1,1, 1, -1};
    } else if(dir <= -7*PI/16 && dir > -PI/2) {
        return {-1,-1,1, 1, 1};
    } else if(dir <= -PI/2 && dir > -9*PI/16 ) {
        return {-1,1,-1, -1, -1};
    } else if(dir <= -9*PI/16 && dir > -5*PI/8) {
        return {-1,1,-1, -1, 1};
    } else if(dir <= -5*PI/8 && dir > -11*PI/16) {
        return {-1,1,-1, 1, -1};
    } else if(dir <= -11*PI/16 && dir > -3*PI/4) {
        return {-1,1,-1, 1, 1};
    } else if(dir <= -3*PI/4 && dir > -13*PI/16) {
        return {-1,1,1,-1, -1};
    } else if(dir <= -13*PI/16 && dir > -7*PI/8) {
        return {-1,1,1, -1, 1};
    } else if(dir <= -7*PI/8 && dir > -15*PI/16) {
        return {-1,1,1, 1, -1};
    } else if(dir <= -15*PI/16 && dir > -PI) {
        return {-1,1,1, 1, 1};
    } else if(dir <= PI && dir > 15*PI/16 ) {
        return {1,-1,-1, -1, -1};
    } else if(dir > 0.0 && dir <= PI/16) {
        return {1,-1,-1, -1, 1};
    } else if(dir > PI/16 && dir <= PI/8) {
        return {1,-1,-1, 1, -1};
    } else if(dir > PI/8 && dir <= 3*PI/16) {
        return {1,-1,-1, 1, 1};
    } else if(dir > 3*PI/16 && dir <= PI/4) {
        return {1,-1,1,-1, -1};
    } else if(dir > PI/4 && dir <= 5*PI/16) {
        return {1,-1,1, -1, 1};
    } else if(dir > 5*PI/16 && dir <= 3*PI/8) {
        return {1,-1,1, 1, -1};
    } else if(dir > 3*PI/8 && dir <= 7*PI/16) {
        return {1,-1,1, 1, 1};
    } else if(dir > 7*PI/16 && dir <= PI/2 ) {
        return {1,1,-1, -1, -1};
    } else if(dir > PI/2 && dir <= 9*PI/16) {
        return {1,1,-1, -1, 1};
    } else if(dir > 9*PI/16 && dir <= 10*PI/16) {
        return {1,1,-1, 1, -1};
    } else if(dir > 10*PI/16 && dir <= 11*PI/16) {
        return {1,1,-1, 1, 1};
    } else if(dir > 11*PI/16 && dir <= 3*PI/4) {
        return {1,1,1,-1, -1};
    } else if(dir > 3*PI/4 && dir <= 13*PI/16) {
        return {1,1,1, -1, 1};
    } else if(dir > 13*PI/16 && dir <= 7*PI/8) {
        return {1,1,1, 1, -1};
    } else if(dir > 7*PI/8 && dir <= 15*PI/16) {
        return {1,1,1, 1, 1};
    } else {
        return {-1,-1, -1, -1,-1};
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
    long puntuacion = 0;

    ControladorSonido csonido;
    Configuracion configuracionGlobal;

    Nave nave({rand() % resolucion.x * 1.0f, rand() % resolucion.y * 1.0f}, resolucion, &puntuacion,
              configuracionGlobal.color(), &csonido);

    if(leer) {
        red = red.read(fichero);
    }

    bool continua = true;
    int aciertos = 0, disparos = 0;
    double tiempo = 0.0;
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

        vector<double> entradasRed{nave.getPosicion().x - sustitutoOvni.getPosition().x,
                                   nave.getPosicion().y - sustitutoOvni.getPosition().y
        };

        double salida = output2Radians(red.run(entradasRed));
        Disparo disparo(sustitutoOvni.getPosition(), salida, resolucion, sf::Color::White);
        disparo.setDireccion((float) salida);
        bool acertado = false;
        while (!acertado && !disparo.comprobarAlcance()) {
            disparo.mover();
            if (disparo.comprobarColision(nave)) {
                acertado = true;
            }
        }
        sf::Vector2f vectorDir = (nave.getPosicion() - sustitutoOvni.getPosition());
        double direccionDisp = atan2(vectorDir.y, vectorDir.x);
        if(abs(salida-direccionDisp) < PI/16) {
            acertado = true;
        }
        if (!acertado) {
            red.trainSingle(entradasRed, radians2Output(direccionDisp), ratioAprendizaje);
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
}