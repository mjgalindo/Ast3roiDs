#include <SFML/Graphics.hpp>

#include "Graficos/Grafico.hpp"

using namespace sf;
using namespace std;

int main() {

    Vector2u MAX_SIZE;

    // Creacion de la ventana
    RenderWindow window;

    for(VideoMode vm : VideoMode::getFullscreenModes()) {
        if(vm.isValid()) {
            window.create(VideoMode::getDesktopMode(), "Ast3roiDs", Style::Fullscreen);
            MAX_SIZE = window.getSize();
            break;
        }
    }

    Vector2f posicion;
    posicion.x = window.getSize().x / 2;
    posicion.y = window.getSize().y / 2;

    Grafico gr = Grafico(posicion);
    gr.setTextura("Imagenes/tx1.png");

    Vector2f posicion2;
    posicion2.x = 5;
    posicion2.y = 5;
    Vector2f velocidad2;
    velocidad2.x = 0.2;
    velocidad2.y = 0.2;

    Grafico gr2 = Grafico(posicion2);
    gr2.setTextura("Imagenes/tx2.png");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {

            switch(event.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::KeyPressed:
                    if(Keyboard::isKeyPressed(Keyboard::Left)){
                        posicion.x -= 2;
                        if(posicion.x<0){
                            posicion.x = MAX_SIZE.x;
                        }
                        gr.setPosicion(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Right)){
                        posicion.x += 2;
                        if(posicion.x>MAX_SIZE.x){
                            posicion.x = 0;
                        }
                        gr.setPosicion(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Up)){
                        posicion.y -= 2;
                        if(posicion.y<0){
                            posicion.y = MAX_SIZE.y;
                        }
                        gr.setPosicion(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Down)){
                        posicion.y += 2;
                        if(posicion.y>MAX_SIZE.y){
                            posicion.y = 0;
                        }
                        gr.setPosicion(posicion);
                    }
                    else if(Keyboard::isKeyPressed(Keyboard::Escape)){
                        window.close();
                    }
            }
        }

        posicion2.x = posicion2.x + velocidad2.x;
        posicion2.y = posicion2.y + velocidad2.y;
        gr2.setPosicion(posicion2);

        if(posicion2.x<0 || posicion2.x+gr2.getAncho()>MAX_SIZE.x){
            velocidad2.x = velocidad2.x * -1;
        }
        if(posicion2.y<0 || posicion2.y+gr2.getAlto()>MAX_SIZE.y){
            velocidad2.y = velocidad2.y * -1;
        }

        // Se borra la pantalla con negro
        window.clear(Color::Black);

        //Se dibuja el circulo
        gr.dibujar(&window);
        gr2.dibujar(&window);

        // Se muestra la ventana
        window.display();
    }

    return 0;
}
