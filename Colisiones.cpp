#include "Colisiones.hpp"

//Colision entre dos circulos, C1(c1,r1) y C2(c2,r2)
bool colisionCirculos(sf::Vector2f c1, float r1, sf::Vector2f c2, float r2){
    float distancia_centros_cuadrada =  distancia2(c1,c2);
    float radios_cuadrado = (r1 + r2) * (r1 + r2);
    return distancia_centros_cuadrada < radios_cuadrado;
}

//Colision entre una lista de vertices y un circulo, VS(v1,v2,...) y C(c,r)
bool colisionVerticesCirculo(sf::VertexArray vs, sf::Vector2f c, float r){
    for(int i=0 ; i<vs.getVertexCount() ; i++){
        float distancia_centro = distancia2(vs[i],c);
        if(distancia_centro<r*r){
            return true;
        }
    }
    return false;
}

//Colision entre una lista de vertices y un triangulo, VS(v1,v2,...) y triangulo(v1,v2,v3)
bool colisionVerticesTriangulo(sf::VertexArray vs, sf::VertexArray triangulo){
    float orientacion_triangulo = orientacionTriangular(triangulo[0],triangulo[1],triangulo[2]);
    for(int i=0 ; i<vs.getVertexCount() ; i++) {
        float orientacion_v0v1P = orientacionTriangular(triangulo[0], triangulo[1], vs[i]);
        float orientacion_v1v2P = orientacionTriangular(triangulo[1], triangulo[2], vs[i]);
        float orientacion_v2v0P = orientacionTriangular(triangulo[2], triangulo[0], vs[i]);
        if((orientacion_triangulo>0 && orientacion_v0v1P>0 && orientacion_v1v2P>0 && orientacion_v2v0P>0) ||
           (orientacion_triangulo<0 && orientacion_v0v1P<0 && orientacion_v1v2P<0 && orientacion_v2v0P<0)){
            return true;
        }
    }
    return false;
}

//Devuelve la distancia al cuadrado entre dos puntos v1 y v2
float distancia2(sf::Vector2f v1, sf::Vector2f v2){
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

//Devuelve la distancia al cuadrado entre dos puntos v1 y v2
float distancia2(sf::Vertex v1, sf::Vector2f v2){
    return (v1.position.x - v2.x) * (v1.position.x - v2.x) + (v1.position.y - v2.y) * (v1.position.y - v2.y);
}

//Devuelve la dorientacion de un triangulo(v1,v2,v3)
float orientacionTriangular(sf::Vertex v1, sf::Vertex v2, sf::Vertex v3){
    return (v1.position.x - v3.position.x) * (v2.position.y - v3.position.y) - (v1.position.y - v3.position.y) * (v2.position.x - v3.position.x);
}