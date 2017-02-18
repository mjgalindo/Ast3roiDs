#include "Grafico.hpp"

//Constructores
Grafico::Grafico(){
    sprite = sf::Sprite();
}

Grafico::Grafico(sf::Sprite sp){
    sprite = sp;
}

Grafico::Grafico(float x, float y){
    sprite = sf::Sprite();
    sprite.setPosition(x,y);
}

Grafico::Grafico(sf::Vector2f pos){
    sprite = sf::Sprite();
    sprite.setPosition(pos);
}

//Destructor
Grafico::~Grafico(){}

//Setters
void Grafico::setPosicion(sf::Vector2f pos){
    sprite.setPosition(pos);
}

void Grafico::setPosicion(float x, float y){
    sprite.setPosition(x,y);
}

void Grafico::setX(float x){
    sprite.setPosition(x,getY());
}

void Grafico::setY(float y){
    sprite.setPosition(getX(),y);
}

void Grafico::setSprite(sf::Sprite sp){
    sprite = sp;
}

void Grafico::setTextura(sf::Texture tx){
    textura = tx;
    sprite.setTexture(textura);
}

bool Grafico::setTextura(std::string pathTx){
    if(textura.loadFromFile(pathTx)) {
        sprite.setTexture(textura);
        return true;
    }
    return false;
}

//Getters
sf::Vector2f Grafico::getPosicion(){
    return sprite.getPosition();
}

float Grafico::getX(){
    return sprite.getPosition().x;
}

float Grafico::getY(){
    return sprite.getPosition().y;
}

sf::Vector2u Grafico::getTamano(){
    return textura.getSize();
}

unsigned int Grafico::getAncho(){
    return textura.getSize().x;
}

unsigned int Grafico::getAlto(){
    return textura.getSize().y;
}

sf::Sprite Grafico::getSprite(){
    return sprite;
}

sf::Texture Grafico::getTx(){
    return textura;
}

//Dibujar
void Grafico::dibujar(sf::RenderWindow* ventana){
    ventana->draw(sprite);
}