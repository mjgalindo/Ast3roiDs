#include <glm/vec3.hpp>
#include "Colisiones.hpp"
#include "matematicas.hpp"

//Colision entre dos circulos, C1(c1,r1) y C2(c2,r2)
bool colisionCirculos(sf::Vector2f c1, float r1, sf::Vector2f c2, float r2) {
    float distancia_centros = distanciaEuclidea(c1, c2);
    return distancia_centros < r1 + r2;
}

//Colision entre una lista de vertices y un circulo, VS(v1,v2,...) y C(c,r)
bool colisionVerticesCirculo(sf::VertexArray vs, sf::Vector2f c, float r) {
    for (int i = 0; i < vs.getVertexCount(); i++) {
        float distancia_centro = distanciaEuclidea(vs[i].position, c);
        if (distancia_centro < r) {
            return true;
        }
    }
    return false;
}

//Colision entre una lista de vertices y un circulo, VS(v1,v2,...) y C(c,r)
bool colisionTrianguloCirculo(sf::VertexArray vs, sf::Vector2f c, float r) {
    vs.append(sf::Vertex(
            sf::Vector2f((vs[0].position.x + vs[1].position.x) / 2.0f, (vs[0].position.y + vs[1].position.y) / 2.0f)));
    vs.append(sf::Vertex(
            sf::Vector2f((vs[1].position.x + vs[2].position.x) / 2.0f, (vs[1].position.y + vs[2].position.y) / 2.0f)));
    vs.append(sf::Vertex(
            sf::Vector2f((vs[2].position.x + vs[0].position.x) / 2.0f, (vs[2].position.y + vs[0].position.y) / 2.0f)));
    for (int i = 0; i < vs.getVertexCount(); i++) {
        float distancia_centro = distanciaEuclidea(vs[i].position, c);
        if (distancia_centro < r) {
            return true;
        }
    }
    return false;
}

//Colision entre una lista de vertices y un triangulo, VS(v1,v2,...) y triangulo(v1,v2,v3)
bool colisionVerticesTriangulo(sf::VertexArray vs, sf::VertexArray triangulo) {
    float orientacion_triangulo = orientacionTriangular(triangulo[0], triangulo[1], triangulo[2]);
    for (int i = 0; i < vs.getVertexCount(); i++) {
        float orientacion_v0v1P = orientacionTriangular(triangulo[0], triangulo[1], vs[i]);
        float orientacion_v1v2P = orientacionTriangular(triangulo[1], triangulo[2], vs[i]);
        float orientacion_v2v0P = orientacionTriangular(triangulo[2], triangulo[0], vs[i]);
        if ((orientacion_triangulo > 0 && orientacion_v0v1P > 0 && orientacion_v1v2P > 0 && orientacion_v2v0P > 0) ||
            (orientacion_triangulo < 0 && orientacion_v0v1P < 0 && orientacion_v1v2P < 0 && orientacion_v2v0P < 0)) {
            return true;
        }
    }
    return false;
}

//Colision entre dos esferas: e(centro,radio)
bool colisionEsferaEsfera(glm::vec3 c1, float r1, glm::vec3 c2, float r2){
    return distanciaEuclidea(c1,c2)<=r1+r2;
}

//Devuelve true si el punto esta dentro de la esfera
bool colisionPuntoEsfera(glm::vec3 p, glm::vec3 c, float r){
    return distanciaEuclidea(p,c)<=r;
}

//Devuelve la dorientacion de un triangulo(v1,v2,v3)
float orientacionTriangular(sf::Vertex v1, sf::Vertex v2, sf::Vertex v3) {
    return (v1.position.x - v3.position.x) * (v2.position.y - v3.position.y) -
           (v1.position.y - v3.position.y) * (v2.position.x - v3.position.x);
}