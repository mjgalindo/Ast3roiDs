#ifndef AST3ROIDS_MATEMATICAS_HPP
#define AST3ROIDS_MATEMATICAS_HPP

#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>

static constexpr double PI = 3.14159265358979323846;

static std::mt19937 enredadorDeMersenne{(unsigned long) time(NULL)};


static float anguloAleatorio() {
    static std::uniform_real_distribution<float> distribucionRadianes((float) -PI, (float) PI);
    return distribucionRadianes(enredadorDeMersenne);
}

static int enteroAleatorio(int minimo, int maximo) {
    std::uniform_int_distribution<int> distribucionTemporal(minimo, maximo);
    return distribucionTemporal(enredadorDeMersenne);
}

static float valorAleatorio(float minimo = 0.0f, float maximo = 1.0f) {
    std::uniform_real_distribution<float> distribucionReales(minimo, maximo);
    return distribucionReales(enredadorDeMersenne);
}

template<typename T>
static T distanciaEuclidea(sf::Vector2<T> a, sf::Vector2<T> b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

template<typename T>
static float distanciaEuclidea(T a, T b) {
    return (float) sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

template<typename T>
static int rad2deg(T radianes) {
    return (int) ((radianes < 0 ? radianes + 2 * PI : radianes) * 180 / PI);
}

template<typename T>
static float tamanoVector(T vector3) {
    return (float) sqrt(pow(vector3.x, 2) + pow(vector3.y, 2) + pow(vector3.z, 2));
}

static glm::quat rotacionAleatoria() {
    return glm::angleAxis(valorAleatorio(0, (float) PI),
                          glm::normalize(glm::vec3(valorAleatorio(), valorAleatorio(), valorAleatorio())));
}

#endif //AST3ROIDS_MATEMATICAS_HPP
