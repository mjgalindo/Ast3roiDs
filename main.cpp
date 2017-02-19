#include <SFML/Graphics.hpp>

using namespace std;

int tratarTitulo(int estado);
int tratarMenu(int estado);
int tratarJuego(int estado);
int tratarGameOver(int estado);
int tratarPuntuaciones(int estado);
int tratarOpciones(int estado);

//Tamaño de la ventana
sf::Vector2u MAX_SIZE;
//Ventana
sf::RenderWindow ventana;

int main() {

    for(sf::VideoMode vm : sf::VideoMode::getFullscreenModes()) {
        if(vm.isValid()) {
            ventana.create(sf::VideoMode::getDesktopMode(), "Ast3roiDs", sf::Style::Fullscreen);
            MAX_SIZE = ventana.getSize();
            break;
        }
    }

    int estado_actual = 0;
    while(ventana.isOpen()){
        switch(estado_actual){
            case 0: //Titulo
                estado_actual = tratarTitulo(estado_actual);
                break;
            case 1: //Menu
                estado_actual = tratarMenu(estado_actual);
                break;
            case 2: //Juego
                estado_actual = tratarJuego(estado_actual);
                break;
            case 3: //Game Over
                estado_actual = tratarGameOver(estado_actual);
                break;
            case 4: //Puntuaciones
                estado_actual = tratarPuntuaciones(estado_actual);
                break;
            case 5: //Opciones
                estado_actual = tratarOpciones(estado_actual);
                break;
            default:
                return 0;
        }
    }
    return 0;
}

int tratarTitulo(int estado){
    sf::Text texto;
    sf::Text instrucciones;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/arial.ttf");

    texto.setFont(fuente);
    texto.setString("TITULO");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    instrucciones.setFont(fuente);
    instrucciones.setString("<ENTER> PARA MENU");
    instrucciones.setCharacterSize(30);
    instrucciones.setPosition(sf::Vector2f(0.0,35.0));
    instrucciones.setFillColor(sf::Color::White);

    while(true){
        sf::Event event;
        while(ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return -1;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        return 1;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(instrucciones);
            ventana.display();
        }
    }
}

int tratarMenu(int estado){
    sf::Text texto;
    sf::Text opcion1;
    sf::Text opcion2;
    sf::Text opcion3;
    sf::Text opcion4;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/arial.ttf");

    texto.setFont(fuente);
    texto.setString("MENU");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-JUEGO");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0,35.0));
    opcion1.setFillColor(sf::Color::White);

    opcion2.setFont(fuente);
    opcion2.setString("2-PUNTUACIONES");
    opcion2.setCharacterSize(30);
    opcion2.setPosition(sf::Vector2f(0.0,70.0));
    opcion2.setFillColor(sf::Color::White);

    opcion3.setFont(fuente);
    opcion3.setString("3-OPCIONES");
    opcion3.setCharacterSize(30);
    opcion3.setPosition(sf::Vector2f(0.0,105.0));
    opcion3.setFillColor(sf::Color::White);

    opcion4.setFont(fuente);
    opcion4.setString("4-SALIR");
    opcion4.setCharacterSize(30);
    opcion4.setPosition(sf::Vector2f(0.0,140.0));
    opcion4.setFillColor(sf::Color::White);


    while(true){
        sf::Event event;
        while(ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return -1;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return 2;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                        return 4;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                        return 5;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                        return -1;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.draw(opcion2);
            ventana.draw(opcion3);
            ventana.draw(opcion4);
            ventana.display();
        }
    }
}

int tratarJuego(int estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/arial.ttf");

    texto.setFont(fuente);
    texto.setString("JUEGO");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-GAME OVER");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return -1;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return 3;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.display();
        }
    }
}

int tratarGameOver(int estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/arial.ttf");

    texto.setFont(fuente);
    texto.setString("GAME OVER");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-PUNTUACIONES");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return -1;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return 4;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.display();
        }
    }
}

int tratarPuntuaciones(int estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/arial.ttf");

    texto.setFont(fuente);
    texto.setString("PUNTUACIONES");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-MENU");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return -1;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return 1;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.display();
        }
    }
}

int tratarOpciones(int estado) {
    sf::Text texto;
    sf::Text opcion1;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/arial.ttf");

    texto.setFont(fuente);
    texto.setString("OPCIONES");
    texto.setCharacterSize(30);
    texto.setFillColor(sf::Color::White);

    opcion1.setFont(fuente);
    opcion1.setString("1-MENU");
    opcion1.setCharacterSize(30);
    opcion1.setPosition(sf::Vector2f(0.0, 35.0));
    opcion1.setFillColor(sf::Color::White);

    while (true) {
        sf::Event event;
        while (ventana.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    ventana.close();
                    return -1;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return 1;
                    }
                default:
                    break;
            }

            ventana.clear(sf::Color::Black);
            ventana.draw(texto);
            ventana.draw(opcion1);
            ventana.display();
        }
    }
}