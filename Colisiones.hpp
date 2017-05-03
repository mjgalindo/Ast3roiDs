#ifndef AST3ROIDS_COLISIONES_HPP
#define AST3ROIDS_COLISIONES_HPP

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

bool colisionCirculos(sf::Vector2f c1, float r1, sf::Vector2f c2, float r2);

bool colisionVerticesCirculo(sf::VertexArray vs, sf::Vector2f c, float r);

bool colisionTrianguloCirculo(sf::VertexArray vs, sf::Vector2f c, float r);

bool colisionVerticesTriangulo(sf::VertexArray vs, sf::VertexArray triangulo);

bool colisionEsferaEsfera(glm::vec3 c1, float r1, glm::vec3 c2, float r2);

bool colisionPuntoEsfera(glm::vec3 p, glm::vec3 c, float r);

//Funciones auxiliares

float orientacionTriangular(sf::Vertex v1, sf::Vertex v2, sf::Vertex v3);


#endif //AST3ROIDS_COLISIONES_HPP
