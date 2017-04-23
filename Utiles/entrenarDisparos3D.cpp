#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos3D/Elemento3D.hpp"
#include "../Graficos3D/Nave3D.hpp"
#include "../Util3D/Ventana3D.hpp"
#include "../neural/include/neural/Network.h"
#include "../Graficos3D/Ovni3D.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

double radioTonto = 15;     //Radio del ovni tonto
double radioInteligente = 3*radioTonto/4;       //Radio del ovni inteligente

//PARAMETROS QUE USARA LA RED
double radio = radioInteligente;        //Radio que empleara la red

double ratioAprendizaje = 0.6;      //Ratio de aprendizaje de la red

string fichero = "disparo3D.nnet";
bool leer = false;

// Inicializa una red neuronal nueva
neural::Network red(3, 3, {12});

int main() {
    sf::ContextSettings configuracion;

    srand((unsigned long) time(NULL));
    // Crea la ventana. El constructor carga las funciones de OpenGL y llama a glewInit() por lo que esto se debe
    // hacer al principio.
    Ventana3D ventana(sf::VideoMode(WIDTH, HEIGHT), "OpenGL", sf::Style::Close | sf::Style::Titlebar, configuracion,0);
    sf::Vector2f posicionAnterior;
    long puntuacion = 0;

    ControladorSonido csonido;

    Nave3D nave(&csonido,&puntuacion);

    Ovni3D sustitutoOvni(&csonido);


    if (leer) {
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
                        if (red.write(fichero)) {
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

        vector<double> entradasRed{nave.pos.posicion.x - sustitutoOvni.pos.posicion.x,
                                   nave.pos.posicion.y - sustitutoOvni.pos.posicion.y,
                                    nave.pos.posicion.z - sustitutoOvni.pos.posicion.z
        };

        vector<double> salida = red.run(entradasRed);
        glm::vec3 direccion = glm::vec3(salida.at(0), salida.at(1), salida.at(2));
        Disparo3D disparo(direccion, sustitutoOvni.pos.posicion,glm::vec3(0.0f,0.0f,0.0f)); //FALTA LA ROTACION
        bool acertado = false;
        while (!acertado && disparo.estado != Elemento3D::Estado3D::DESTRUIDO) {
            disparo.actualizar();
            if (colisionPuntoEsfera(disparo.pos.posicion,nave.pos.posicion,7.6f * nave.pos.escala.z)) {
                acertado = true;
            }
        }
        glm::vec3 dirReal = (nave.pos.posicion - sustitutoOvni.pos.posicion);
        if (!acertado) {
            red.trainSingle(entradasRed, {dirReal.x, dirReal.y, dirReal.z}, ratioAprendizaje);
            cout << aciertos << " " << disparos << " Fallo" << endl;
        } else {
            aciertos++;
            cout << aciertos << " " << disparos << " Acierto" << endl;
            disparos = 0;
        }
        sustitutoOvni.pos.posicion={valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f)};
        nave.pos.posicion={valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f), valorAleatorio(-80.0f, 80.0f)};
        disparos++;
    }
}