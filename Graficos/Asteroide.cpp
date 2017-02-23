#include "Asteroide.hpp"


Asteroide::Asteroide(sf::Vector2f posicion_inicial, float dir, sf::Vector2f vel, int v, float s){

    posicion = posicion_inicial;
    direccion = dir;
    velocidad = vel;
    size = s;
    version = v;
     switch(v){
         case 0:
             puntos[0] = sf::Vector2f(-12, -5.7);
             puntos[1] = sf::Vector2f(-12.3, -3.7);
             puntos[2] = sf::Vector2f(-4.7, 8.5);
             puntos[3] = sf::Vector2f(4.3, 8.7);
             puntos[4] = sf::Vector2f(13, 3.3);
             puntos[5] = sf::Vector2f(9.7, -1);
             puntos[6] = sf::Vector2f(9.5, -8.3);
             puntos[7] = sf::Vector2f(6.3, -13.5);
             puntos[8] = sf::Vector2f(0.5, -7.7);
             puntos[9] = sf::Vector2f(-5.7, -13.0);
             break;
         case 1:
             puntos[0] = sf::Vector2f(-6, -11.2);
             puntos[1] = sf::Vector2f(-2.5, -5.5);
             puntos[2] = sf::Vector2f(-11.5, -5.5);
             puntos[3] = sf::Vector2f(-11.8, 3.0);
             puntos[4] = sf::Vector2f(-3.8, 12.0);
             puntos[5] = sf::Vector2f(4.0, 8.8);
             puntos[6] = sf::Vector2f(6.8, 12.5);
             puntos[7] = sf::Vector2f(12.2, 5.5);
             puntos[8] = sf::Vector2f(5.2, 1);
             puntos[9] = sf::Vector2f(13.2, -2.0);
             puntos[10] = sf::Vector2f(16.2, -5.5);
             puntos[11] = sf::Vector2f(4.2, -10.8);
             break;
         case 2:
             puntos[0] = sf::Vector2f(-4.6, -11.2);
             puntos[1] = sf::Vector2f(-11.0, -5.4);
             puntos[2] = sf::Vector2f(-7.6, -1.0);
             puntos[3] = sf::Vector2f(-10.8, 5.8);
             puntos[4] = sf::Vector2f(-4.8, 11.8);
             puntos[5] = sf::Vector2f(-1.0, 8.0);
             puntos[6] = sf::Vector2f(6.7, 10.3);
             puntos[7] = sf::Vector2f(12.7, 2.6);
             puntos[8] = sf::Vector2f(7.4, -2.7);
             puntos[9] = sf::Vector2f(12.2, -5.7);
             puntos[10] = sf::Vector2f(7.0, -11.0);

     }
}

//Getters
sf::Vector2f* Asteroide::getPuntos(){
    return puntos;
}

float Asteroide::getDireccion(){
    return direccion;
}

sf::Vector2f Asteroide::getPosicion(){
    return posicion;
}

sf::Vector2f Asteroide::getVelocidad(){
    return velocidad;
}
void Asteroide::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    sf::Vertex v1 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[0].x*cos(direccion)-size*puntos[0].y*sin(direccion),posicion.y+size*puntos[0].y*cos(direccion)+size*puntos[0].x*sin(direccion)),sf::Color::White);
    sf::Vertex v2 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[1].x*cos(direccion)-size*puntos[1].y*sin(direccion),posicion.y+size*puntos[1].y*cos(direccion)+size*puntos[1].x*sin(direccion)),sf::Color::White);
    sf::Vertex v3 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[2].x*cos(direccion)-size*puntos[2].y*sin(direccion),posicion.y+size*puntos[2].y*cos(direccion)+size*puntos[2].x*sin(direccion)),sf::Color::White);
    sf::Vertex v4 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[3].x*cos(direccion)-size*puntos[3].y*sin(direccion),posicion.y+size*puntos[3].y*cos(direccion)+size*puntos[3].x*sin(direccion)),sf::Color::White);
    sf::Vertex v5 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[4].x*cos(direccion)-size*puntos[4].y*sin(direccion),posicion.y+size*puntos[4].y*cos(direccion)+size*puntos[4].x*sin(direccion)),sf::Color::White);
    sf::Vertex v6 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[5].x*cos(direccion)-size*puntos[5].y*sin(direccion),posicion.y+size*puntos[5].y*cos(direccion)+size*puntos[5].x*sin(direccion)),sf::Color::White);
    sf::Vertex v7 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[6].x*cos(direccion)-size*puntos[6].y*sin(direccion),posicion.y+size*puntos[6].y*cos(direccion)+size*puntos[6].x*sin(direccion)),sf::Color::White);
    sf::Vertex v8 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[7].x*cos(direccion)-size*puntos[7].y*sin(direccion),posicion.y+size*puntos[7].y*cos(direccion)+size*puntos[7].x*sin(direccion)),sf::Color::White);
    sf::Vertex v9 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[8].x*cos(direccion)-size*puntos[8].y*sin(direccion),posicion.y+size*puntos[8].y*cos(direccion)+size*puntos[8].x*sin(direccion)),sf::Color::White);
    sf::Vertex v10 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[9].x*cos(direccion)-size*puntos[9].y*sin(direccion),posicion.y+size*puntos[9].y*cos(direccion)+size*puntos[9].x*sin(direccion)),sf::Color::White);

    sf::Vertex linea1[] = {v1,v2};
    sf::Vertex linea2[] = {v2,v3};
    sf::Vertex linea3[] = {v3,v4};
    sf::Vertex linea4[] = {v4,v5};
    sf::Vertex linea5[] = {v5,v6};
    sf::Vertex linea6[] = {v6,v7};
    sf::Vertex linea7[] = {v7,v8};
    sf::Vertex linea8[] = {v8,v9};
    sf::Vertex linea9[] = {v9,v10};

    if(version < 0){
        sf::Vertex v11 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[10].x*cos(direccion)-size*puntos[10].y*sin(direccion),posicion.y+size*puntos[10].y*cos(direccion)+size*puntos[10].x*sin(direccion)),sf::Color::White);
        if(version == 1){
            sf::Vertex v12 = sf::Vertex(sf::Vector2f(posicion.x+size*puntos[11].x*cos(direccion)-size*puntos[11].y*sin(direccion),posicion.y+size*puntos[11].y*cos(direccion)+size*puntos[11].x*sin(direccion)),sf::Color::White);
            sf::Vertex linea11[] = {v11,v12};
            sf::Vertex linea12[] = {v12,v1};

            target.draw(linea11, 2, sf::Lines);
            target.draw(linea12, 2, sf::Lines);
        }
        else{
            sf::Vertex linea11[] = {v11,v1};

            target.draw(linea11, 2, sf::Lines);
        }
        sf::Vertex linea10[] = {v10,v11};

        target.draw(linea10, 2, sf::Lines);
    }
    else{
        sf::Vertex linea10[] = {v10,v1};

        target.draw(linea10, 2, sf::Lines);
    }


    target.draw(linea1, 2, sf::Lines);
    target.draw(linea2, 2, sf::Lines);
    target.draw(linea3, 2, sf::Lines);
    target.draw(linea4, 2, sf::Lines);
    target.draw(linea5, 2, sf::Lines);
    target.draw(linea6, 2, sf::Lines);
    target.draw(linea7, 2, sf::Lines);
    target.draw(linea8, 2, sf::Lines);
    target.draw(linea9, 2, sf::Lines);

}