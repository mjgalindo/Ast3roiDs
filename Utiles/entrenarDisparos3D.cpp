#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Graficos3D/Elemento3D.hpp"
#include "../Graficos3D/Nave3D.hpp"
#include "../Util3D/Ventana3D.hpp"

#define WIDTH 800
#define HEIGHT 600

using namespace std;

float limiteMovimiento = 100;


double ratioAprendizaje = 0.6;      //Ratio de aprendizaje de la red

float radioNave = 7.6f;
float dispAcierto = radioNave * 2.0f;

string fichero = "disparo3D.nnet";
bool leer = false;

// Inicializa una red neuronal nueva
neural::Network red(3, 3, {9});

vector<double> out2dir(vector<double> outReal) {
    vector<double> out;
    for(unsigned long long int i = 0; i < outReal.size(); i++){
        if(outReal.at(i) < 0) {
            out.push_back(0);
        } else {
            out.push_back(1);
        }
    }
    if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-1.0, -1.0, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-1.0, -1.0, -0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {-1.0, -1.0, 0.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {-1.0, -1.0, 0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {-1.0, -1.0, 1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {-1.0, -0.5, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {-1.0, -0.5, -0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {-1.0, -0.5, 0.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-1.0, -0.5, 0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-1.0, -0.5, 1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {-1.0, 0.0, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {-1.0, 0.0, -0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {-1.0, 0.0, 0.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {-1.0, 0.0, 0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {-1.0, 0.0, 1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {-1.0, 0.5, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-1.0, 0.5, -0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-1.0, 0.5, 0.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {-1.0, 0.5, 0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {-1.0, 0.5, 1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {-1.0, 1.0, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {-1.0, 1.0, -0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {-1.0, 1.0, 0.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {-1.0, 1.0, 0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-1.0, 1.0, 1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-0.5, -1.0, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {-0.5, -1.0, -0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {-0.5, -1.0, 0.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {-0.5, -1.0, 0.5};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {-0.5, -1.0, 1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {-0.5, -0.5, -1.0};
    } else if(out[0] == 0 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {-0.5, -0.5, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-0.5, -0.5, 0.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-0.5, -0.5, 0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {-0.5, -0.5, 1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {-0.5, 0.0, -1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {-0.5, 0.0, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {-0.5, 0.0, 0.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {-0.5, 0.0, 0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {-0.5, 0.0, 1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-0.5, 0.5, -1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-0.5, 0.5, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {-0.5, 0.5, 0.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {-0.5, 0.5, 0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {-0.5, 0.5, 1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {-0.5, 1.0, -1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {-0.5, 1.0, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {-0.5, 1.0, 0.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {-0.5, 1.0, 0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {-0.5, 1.0, 1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.0, -1.0, -1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.0, -1.0, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {0.0, -1.0, 0.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {0.0, -1.0, 0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {0.0, -1.0, 1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {0.0, -0.5, -1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {0.0, -0.5, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {0.0, -0.5, 0.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.0, -0.5, 0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.0, -0.5, 1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {0.0, 0.0, -1.0};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {0.0, 0.0, -0.5};
    } else if(out[0] == 0 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {0.0, 0.0, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {0.0, 0.0, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {0.0, 0.5, -1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.0, 0.5, -0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.0, 0.5, 0.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {0.0, 0.5, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {0.0, 0.5, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {0.0, 1.0, -1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {0.0, 1.0, -0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {0.0, 1.0, 0.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {0.0, 1.0, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.0, 1.0, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.5, -1.0, -1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {0.5, -1.0, -0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {0.5, -1.0, 0.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {0.5, -1.0, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {0.5, -1.0, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {0.5, -0.5, -1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {0.5, -0.5, -0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.5, -0.5, 0.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.5, -0.5, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {0.5, -0.5, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {0.5, 0.0, -1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {0.5, 0.0, -0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {0.5, 0.0, 0.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {0.5, 0.0, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {0.5, 0.0, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.5, 0.5, -1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.5, 0.5, -0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {0.5, 0.5, 0.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {0.5, 0.5, 0.5};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {0.5, 0.5, 1.0};
    } else if(out[0] == 1 && out[1] == 0 && out[2] == 1 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {0.5, 1.0, -1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {0.5, 1.0, -0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {0.5, 1.0, 0.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {0.5, 1.0, 0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {0.5, 1.0, 1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {1.0, -1.0, -1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {1.0, -1.0, -0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {1.0, -1.0, 0.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {1.0, -1.0, 0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {1.0, -1.0, 1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {1.0, -0.5, -1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {1.0, -0.5, -0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {1.0, -0.5, 0.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {1.0, -0.5, 0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {1.0, -0.5, 1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {1.0, 0.0, -1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 0 &&out[3] == 1 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {1.0, 0.0, -0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {1.0, 0.0, 0.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {1.0, 0.0, 0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {1.0, 0.0, 1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {1.0, 0.5, -1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 0) {
        return {1.0, 0.5, -0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 0 && out[6] == 1) {
        return {1.0, 0.5, 0.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 0) {
        return {1.0, 0.5, 0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 0 && out[4] == 1 && out[5] == 1 && out[6] == 1) {
        return {1.0, 0.5, 1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 0) {
        return {1.0, 1.0, -1.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 0 && out[6] == 1) {
        return {1.0, 1.0, -0.5};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 0) {
        return {1.0, 1.0, 0.0};
    } else if(out[0] == 1 && out[1] == 1 && out[2] == 1 &&out[3] == 1 && out[4] == 0 && out[5] == 1 && out[6] == 1) {
        return {1.0, 1.0, 0.5};
    } else {
        return {1.0, 1.0, 1.0};
    }
}

vector<double> dir2out(vector<double> dir) {
    if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 0, 0, 0, 0, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 0, 0, 0, 0, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 0, 0, 0, 0, 1, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 0, 0, 0, 0, 1, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 1.0)) {
        return {0, 0, 0, 0, 1, 0, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 0, 0, 1, 0, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 0, 0, 1, 1, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 0, 0, 0, 1, 1, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 0, 0, 1, 0, 0, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 1.0)) {
        return {0, 0, 0, 1, 0, 0, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 0, 1, 0, 1, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 0, 1, 0, 1, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 0, 0, 1, 1, 0, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 0, 0, 1, 1, 0, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 1.0)) {
        return {0, 0, 0, 1, 1, 1, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 0, 1, 1, 1, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 1, 0, 0, 0, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 0, 1, 0, 0, 0, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 0, 1, 0, 0, 1, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 1.0)) {
        return {0, 0, 1, 0, 0, 1, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 1, 0, 1, 0, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 1, 0, 1, 0, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 0, 1, 0, 1, 1, 0};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 0, 1, 0, 1, 1, 1};
    } else if((dir[0] >= -1.0 && dir[0] < -0.5) && (dir[1] >= 1.0) && (dir[2] >= 1.0)) {
        return {0, 0, 1, 1, 0, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 1, 1, 0, 0, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 1, 1, 0, 1, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 0, 1, 1, 0, 1, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 0, 1, 1, 1, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 1.0)) {
        return {0, 0, 1, 1, 1, 0, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 0, 1, 1, 1, 1, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 0, 1, 1, 1, 1, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 0, 0, 0, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 0, 0, 0, 0, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 1.0)) {
        return {0, 1, 0, 0, 0, 1, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 1, 0, 0, 0, 1, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 1, 0, 0, 1, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 0, 0, 1, 0, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 0, 0, 1, 1, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 1.0)) {
        return {0, 1, 0, 0, 1, 1, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 1, 0, 1, 0, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 1, 0, 1, 0, 0, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 0, 1, 0, 1, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 0, 1, 0, 1, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 1.0)) {
        return {0, 1, 0, 1, 1, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 1, 0, 1, 1, 0, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 1, 0, 1, 1, 1, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 0, 1, 1, 1, 1};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 1, 0, 0, 0, 0};
    } else if((dir[0] >= -0.5 && dir[0] < 0.0) && (dir[1] >= 1.0) && (dir[2] >= 1.0)) {
        return {0, 1, 1, 0, 0, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 1, 1, 0, 0, 1, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 1, 1, 0, 0, 1, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 1, 0, 1, 0, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 1, 0, 1, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 1.0)) {
        return {0, 1, 1, 0, 1, 1, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 1, 1, 0, 1, 1, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 1, 1, 1, 0, 0, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 1, 1, 0, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 1, 1, 0, 1, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 1.0)) {
        return {0, 1, 1, 1, 0, 1, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {0, 1, 1, 1, 1, 0, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {0, 1, 1, 1, 1, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {0, 1, 1, 1, 1, 1, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {0, 1, 1, 1, 1, 1, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 1.0)) {
        return {1, 0, 0, 0, 0, 0, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 0, 0, 0, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 0, 0, 0, 0, 1, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 0, 0, 0, 0, 1, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 0, 0, 0, 1, 0, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 1.0)) {
        return {1, 0, 0, 0, 1, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 0, 0, 1, 1, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 0, 0, 0, 1, 1, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 0, 0, 1, 0, 0, 0};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 0, 0, 1, 0, 0, 1};
    } else if((dir[0] >= 0.0 && dir[0] < 0.5) && (dir[1] >= 1.0) && (dir[2] >= 1.0)) {
        return {1, 0, 0, 1, 0, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 0, 1, 0, 1, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 0, 0, 1, 1, 0, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 0, 0, 1, 1, 0, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 0, 0, 1, 1, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 1.0)) {
        return {1, 0, 0, 1, 1, 1, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 1, 0, 0, 0, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 0, 1, 0, 0, 0, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 0, 1, 0, 0, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 0, 1, 0, 0, 1, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 1.0)) {
        return {1, 0, 1, 0, 1, 0, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 1, 0, 1, 0, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 0, 1, 0, 1, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 0, 1, 0, 1, 1, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 0, 1, 1, 0, 0, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 1.0)) {
        return {1, 0, 1, 1, 0, 0, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 1, 1, 0, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 0, 1, 1, 0, 1, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 0, 1, 1, 1, 0, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 0, 1, 1, 1, 0, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 1.0)) {
        return {1, 0, 1, 1, 1, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 0, 1, 1, 1, 1, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 1, 0, 0, 0, 0, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 1, 0, 0, 0, 0, 1};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 1, 0, 0, 0, 1, 0};
    } else if((dir[0] >= 0.5 && dir[0] < 1.0) && (dir[1] >= 1.0) && (dir[2] >= 1.0)) {
        return {1, 1, 0, 0, 0, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 1, 0, 0, 1, 0, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 1, 0, 0, 1, 0, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 1, 0, 0, 1, 1, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 1, 0, 0, 1, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= -1.0 && dir[1] < -0.5) && (dir[2] >= 1.0)) {
        return {1, 1, 0, 1, 0, 0, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 1, 0, 1, 0, 0, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 1, 0, 1, 0, 1, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 1, 0, 1, 0, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 1, 0, 1, 1, 0, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= -0.5 && dir[1] < 0.0) && (dir[2] >= 1.0)) {
        return {1, 1, 0, 1, 1, 0, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 1, 0, 1, 1, 1, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 1, 0, 1, 1, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 1, 1, 0, 0, 0, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 1, 1, 0, 0, 0, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.0 && dir[1] < 0.5) && (dir[2] >= 1.0)) {
        return {1, 1, 1, 0, 0, 1, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 1, 1, 0, 0, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 1, 1, 0, 1, 0, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 1, 1, 0, 1, 0, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 1, 1, 0, 1, 1, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 0.5 && dir[1] < 1.0) && (dir[2] >= 1.0)) {
        return {1, 1, 1, 0, 1, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 1.0) && (dir[2] >= -1.0 && dir[1] < -0.5)) {
        return {1, 1, 1, 1, 0, 0, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 1.0) && (dir[2] >= -0.5 && dir[1] < 0.0)) {
        return {1, 1, 1, 1, 0, 0, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 1.0) && (dir[2] >= 0.0 && dir[1] < 0.5)) {
        return {1, 1, 1, 1, 0, 1, 0};
    } else if((dir[0] >= 1.0) && (dir[1] >= 1.0) && (dir[2] >= 0.5 && dir[1] < 1.0)) {
        return {1, 1, 1, 1, 0, 1, 1};
    } else if((dir[0] >= 1.0) && (dir[1] >= 1.0) && (dir[2] >= 1.0)) {
        return {1, 1, 1, 1, 1, 0, 0};
    } else {
        return {0, 0, 0, 0, 0, 0, 0};
    }
}

int main() {
    sf::ContextSettings configuracion;

    srand((unsigned long) time(NULL));
    // Crea la ventana. El constructor carga las funciones de OpenGL y llama a glewInit() por lo que esto se debe
    // hacer al principio.
    Ventana3D ventana(sf::VideoMode(WIDTH, HEIGHT), "OpenGL", sf::Style::Close | sf::Style::Titlebar, configuracion,0);
    sf::Vector2f posicionAnterior;
    long puntuacion = 0;

    ControladorSonido csonido;

    Nave3D nave(&csonido,&puntuacion, limiteMovimiento);

    Ovni3D sustitutoOvni(&csonido, limiteMovimiento);


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

        vector<double> entradasRed{nave.pos.posicion.x - sustitutoOvni.pos.posicion.x,
                                   nave.pos.posicion.y - sustitutoOvni.pos.posicion.y,
                                    nave.pos.posicion.z - sustitutoOvni.pos.posicion.z
        };

        vector<double> salida = (red.run(entradasRed));
        glm::vec3 direccion = glm::normalize(glm::vec3(salida.at(0), salida.at(1), salida.at(2)));

        Disparo3D disparo(direccion, sustitutoOvni.pos.posicion,glm::vec3(0.0f,0.0f,0.0f),limiteMovimiento); //FALTA LA ROTACION
        bool acertado = false;
        while (!acertado && disparo.estado != Estado3D::DESTRUIDO_3D) {
            disparo.actualizar();
            if (colisionPuntoEsfera(disparo.pos.posicion,nave.pos.posicion,dispAcierto * nave.pos.escala.z)) {
                acertado = true;
            }
        }
        glm::vec3 dirReal = glm::normalize((nave.pos.posicion - sustitutoOvni.pos.posicion));

        if (!acertado) {
            red.trainSingle(entradasRed, {dirReal.x,dirReal.y,dirReal.z}, ratioAprendizaje);
            cout << aciertos << " " << disparos << " Fallo" << endl;
        } else {
            aciertos++;
            cout << aciertos << " " << disparos << " Acierto" << endl;
            disparos = 0;
        }
        sustitutoOvni.pos.posicion={
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
        };
        nave.pos.posicion={
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
                valorAleatorio(0.8f * -limiteMovimiento, 0.8f * limiteMovimiento),
        };
        disparos++;
    }
}