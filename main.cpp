#include <SFML/Graphics.hpp>

using namespace std;

enum Estado {TITULO, MENU, JUEGO, GAME_OVER, PUNTUACIONES, OPCIONES, ERROR};

Estado tratarTitulo(Estado estado);
Estado tratarMenu(Estado estado);
Estado tratarJuego(Estado estado);
Estado tratarGameOver(Estado estado);
Estado tratarPuntuaciones(Estado estado);
Estado tratarOpciones(Estado estado);

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

    Estado estado_actual = TITULO;
    while(ventana.isOpen()){
        switch(estado_actual){
            case TITULO:
                estado_actual = tratarTitulo(estado_actual);
                break;
            case MENU:
                estado_actual = tratarMenu(estado_actual);
                break;
            case JUEGO:
                estado_actual = tratarJuego(estado_actual);
                break;
            case GAME_OVER:
                estado_actual = tratarGameOver(estado_actual);
                break;
            case PUNTUACIONES:
                estado_actual = tratarPuntuaciones(estado_actual);
                break;
            case OPCIONES:
                estado_actual = tratarOpciones(estado_actual);
                break;
            default:
                return 0;
        }
    }
    return 0;
}

Estado tratarTitulo(Estado estado){
    sf::Text texto;
    sf::Text instrucciones;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

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
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        return MENU;
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

Estado tratarMenu(Estado estado){
    sf::Text texto;
    sf::Text opcion1;
    sf::Text opcion2;
    sf::Text opcion3;
    sf::Text opcion4;

    sf::Font fuente;
    fuente.loadFromFile("Recursos/Fuentes/atari.ttf");

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
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return JUEGO;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                        return PUNTUACIONES;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                        return OPCIONES;
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                        return ERROR;
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

Estado tratarJuego(Estado estado) {
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
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return GAME_OVER;
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

Estado tratarGameOver(Estado estado) {
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
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return PUNTUACIONES;
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

Estado tratarPuntuaciones(Estado estado) {
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
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return TITULO;
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

Estado tratarOpciones(Estado estado) {
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
                    return ERROR;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                        return TITULO;
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
